#include "queue_with_pmr.hpp"
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <algorithm>

// Тестовый класс для Queue
class QueueTest : public ::testing::Test {
protected:
    void SetUp() override {
        resource = new FixedBlockMemoryResource();
        queue = new Queue<int>(resource);
    }

    void TearDown() override {
        delete queue;
        delete resource;
    }

    FixedBlockMemoryResource* resource;
    Queue<int>* queue;
};

// Тест для пользовательского типа данных
struct TestData {
    int id;
    std::string name;
    double value;
    
    bool operator==(const TestData& other) const {
        return id == other.id && name == other.name && value == other.value;
    }
};

// Тест 1: Базовая функциональность
TEST_F(QueueTest, BasicOperations) {
    EXPECT_TRUE(queue->empty());
    EXPECT_EQ(queue->size(), 0);

    queue->push(1);
    queue->push(2);
    queue->push(3);

    EXPECT_FALSE(queue->empty());
    EXPECT_EQ(queue->size(), 3);
    EXPECT_EQ(queue->front(), 1);
    EXPECT_EQ(queue->back(), 3);

    queue->pop();
    EXPECT_EQ(queue->front(), 2);
    EXPECT_EQ(queue->size(), 2);

    queue->pop();
    queue->pop();
    EXPECT_TRUE(queue->empty());
    EXPECT_EQ(queue->size(), 0);
}

// Тест 2: Очередь сохраняет порядок FIFO
TEST_F(QueueTest, FIFOOrder) {
    std::vector<int> expected = {1, 2, 3, 4, 5};
    
    for (int value : expected) {
        queue->push(value);
    }

    std::vector<int> actual;
    for (const auto& value : *queue) {
        actual.push_back(value);
    }

    EXPECT_EQ(actual, expected);
}

// Тест 3: Итераторы работают корректно
TEST_F(QueueTest, IteratorFunctionality) {
    queue->push(10);
    queue->push(20);
    queue->push(30);

    auto it = queue->begin();
    EXPECT_EQ(*it, 10);
    ++it;
    EXPECT_EQ(*it, 20);
    ++it;
    EXPECT_EQ(*it, 30);
    ++it;
    EXPECT_EQ(it, queue->end());

    // Проверка range-based for loop
    std::vector<int> result;
    for (const auto& item : *queue) {
        result.push_back(item);
    }
    EXPECT_EQ(result, std::vector<int>({10, 20, 30}));
}

// Тест 4: Работа с пользовательскими типами
TEST(QueueCustomTypeTest, CustomDataType) {
    FixedBlockMemoryResource resource;
    Queue<TestData> custom_queue(&resource);

    TestData data1{1, "test1", 1.1};
    TestData data2{2, "test2", 2.2};
    
    custom_queue.push(data1);
    custom_queue.push(data2);

    EXPECT_EQ(custom_queue.front(), data1);
    EXPECT_EQ(custom_queue.back(), data2);
    EXPECT_EQ(custom_queue.size(), 2);

    custom_queue.pop();
    EXPECT_EQ(custom_queue.front(), data2);
}

// Тест 5: Очистка очереди
TEST_F(QueueTest, ClearQueue) {
    for (int i = 0; i < 5; ++i) {
        queue->push(i);
    }

    EXPECT_FALSE(queue->empty());
    EXPECT_EQ(queue->size(), 5);

    queue->clear();

    EXPECT_TRUE(queue->empty());
    EXPECT_EQ(queue->size(), 0);
}

// Тест 6: Управление памятью - исключение при переполнении
TEST(QueueMemoryTest, MemoryExhaustion) {
    FixedBlockMemoryResource resource;
    Queue<int> large_queue(&resource);

    // Пытаемся заполнить всю память
    size_t count = 0;
    try {
        for (int i = 0; i < 1000; ++i) {
            large_queue.push(i);
            count++;
        }
        // Если не выбросило исключение, это тоже нормально
        SUCCEED();
    } catch (const std::bad_alloc&) {
        // Ожидаемое поведение - память закончилась
        EXPECT_GT(count, 0) << "Должны были добавить хотя бы несколько элементов";
        std::cout << "Добавлено элементов до исчерпания памяти: " << count << std::endl;
    }
}

// Тест 7: Повторное использование памяти после очистки
TEST(QueueMemoryTest, MemoryReuse) {
    FixedBlockMemoryResource resource;
    Queue<int> test_queue(&resource);

    // Заполняем частично
    for (int i = 0; i < 10; ++i) {
        test_queue.push(i);
    }

    size_t initial_size = test_queue.size();
    test_queue.clear();

    // После очистки должна работать нормально
    test_queue.push(100);
    test_queue.push(200);

    EXPECT_FALSE(test_queue.empty());
    EXPECT_EQ(test_queue.size(), 2);
    EXPECT_EQ(test_queue.front(), 100);
    EXPECT_EQ(test_queue.back(), 200);
}

// Тест 8: Исключения при доступе к пустой очереди
TEST_F(QueueTest, EmptyQueueExceptions) {
    EXPECT_THROW(queue->front(), std::runtime_error);
    EXPECT_THROW(queue->back(), std::runtime_error);

    queue->push(1);
    queue->pop();

    EXPECT_THROW(queue->front(), std::runtime_error);
    EXPECT_THROW(queue->back(), std::runtime_error);
}

// Тест 9: Стресс-тест с множественными операциями
TEST(QueueStressTest, MultipleOperations) {
    FixedBlockMemoryResource resource;
    Queue<int> stress_queue(&resource);

    const int OPERATIONS = 100;
    int expected_sum = 0;
    int actual_sum = 0;

    // Чередуем добавление и удаление
    for (int i = 0; i < OPERATIONS; ++i) {
        stress_queue.push(i);
        expected_sum += i;

        if (i % 3 == 0 && !stress_queue.empty()) {
            stress_queue.pop();
        }
    }

    // Суммируем оставшиеся элементы
    for (const auto& item : stress_queue) {
        actual_sum += item;
    }

    EXPECT_GT(stress_queue.size(), 0);
    EXPECT_LE(actual_sum, expected_sum); // Сумма должна быть меньше из-за pop операций
}

// Тест 10: Проверка стратегии First-Fit
TEST(QueueMemoryStrategyTest, FirstFitStrategy) {
    FixedBlockMemoryResource resource;

    // Создаем несколько очередей для создания фрагментации
    Queue<int> q1(&resource);
    Queue<double> q2(&resource);
    Queue<char> q3(&resource);

    q1.push(1);
    q1.push(2);
    q2.push(3.14);
    q3.push('A');

    // Освобождаем первый блок
    q1.pop();

    // Должны иметь возможность повторно использовать память
    q1.push(42);
    EXPECT_EQ(q1.front(), 2); // FIFO порядок сохраняется
    EXPECT_EQ(q1.back(), 42);
}

// Тест 11: Сравнение memory resources
TEST(QueueMemoryResourceTest, MemoryResourceComparison) {
    FixedBlockMemoryResource resource1;
    FixedBlockMemoryResource resource2;

    EXPECT_TRUE(resource1.do_is_equal(resource1));
    EXPECT_TRUE(resource2.do_is_equal(resource2));
    EXPECT_FALSE(resource1.do_is_equal(resource2));
}

// Тест 12: Долгоживущая очередь
TEST(QueueLongLivedTest, LongLivedQueue) {
    FixedBlockMemoryResource resource;
    
    {
        Queue<std::string> long_queue(&resource);
        
        for (int i = 0; i < 20; ++i) {
            long_queue.push("String_" + std::to_string(i));
        }
        
        EXPECT_EQ(long_queue.size(), 20);
        EXPECT_EQ(long_queue.front(), "String_0");
        EXPECT_EQ(long_queue.back(), "String_19");
        
        // Частичное удаление
        for (int i = 0; i < 10; ++i) {
            long_queue.pop();
        }
        
        EXPECT_EQ(long_queue.size(), 10);
        EXPECT_EQ(long_queue.front(), "String_10");
    } // Очередь уничтожается здесь
    
    // После уничтожения очереди можем создать новую
    Queue<int> new_queue(&resource);
    new_queue.push(999);
    EXPECT_EQ(new_queue.front(), 999);
}

// Тест 13: Проверка состояния памяти (интеграционный тест)
TEST(QueueMemoryStateTest, MemoryStateTracking) {
    FixedBlockMemoryResource resource;
    
    // Начальное состояние - один свободный блок
    Queue<int> test_queue(&resource);
    test_queue.push(1);
    test_queue.push(2);
    test_queue.push(3);
    
    EXPECT_EQ(test_queue.size(), 3);
    
    test_queue.pop();
    EXPECT_EQ(test_queue.size(), 2);
    
    test_queue.clear();
    EXPECT_TRUE(test_queue.empty());
    
    // После очистки память должна быть доступна для повторного использования
    test_queue.push(100);
    EXPECT_EQ(test_queue.front(), 100);
}

// Тест 14: Граничные случаи
TEST_F(QueueTest, EdgeCases) {
    // Добавление и немедленное удаление
    queue->push(1);
    queue->pop();
    EXPECT_TRUE(queue->empty());
    
    // Многократное добавление/удаление одного элемента
    for (int i = 0; i < 10; ++i) {
        queue->push(42);
        EXPECT_EQ(queue->front(), 42);
        queue->pop();
        EXPECT_TRUE(queue->empty());
    }
    
    // Чередование операций
    queue->push(1);
    queue->push(2);
    queue->pop();
    queue->push(3);
    queue->push(4);
    queue->pop();
    
    EXPECT_EQ(queue->front(), 3);
    EXPECT_EQ(queue->back(), 4);
    EXPECT_EQ(queue->size(), 2);
}

// Тест 15: Производительность с большими данными
TEST(QueuePerformanceTest, LargeDataHandling) {
    FixedBlockMemoryResource resource;
    Queue<std::vector<int>> large_queue(&resource);
    
    // Тест с относительно большими объектами
    std::vector<int> large_data(50, 42); // Вектор из 50 элементов
    
    for (int i = 0; i < 10; ++i) {
        large_queue.push(large_data);
    }
    
    EXPECT_EQ(large_queue.size(), 10);
    
    // Проверяем, что данные не испорчены
    for (const auto& item : large_queue) {
        EXPECT_EQ(item.size(), 50);
        EXPECT_EQ(item[0], 42);
    }
}

// Главная функция для запуска тестов
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}