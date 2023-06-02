#include <thread>
#include <deque>
#include <chrono>
#include <mutex>
#include <ctime>


       

struct Checkout {
    bool in_use;
    std::thread* thrd;
    long sum_work_time;
};

struct Customer {
    int id;
    int product_count;
    std::chrono::system_clock::time_point start_customer;
};

class Shop {
 private:
    int checkout_count; // ���������� ����
    int product_processing_time; //����� ��������� ������ �� �����
    int max_line_length; // ������������ ����� �������

    int served_customers_count=0; //���������� ����������� ��������
    int unserved_customers_count=0; // ���������� ������������� ��������
    long sum_line_length=0; // ����� ������������ ����� ����� �� ����� ��� 
                            // ���������� ������� �����
    long sum_customer_time=0; // ��������� ����� ���������� ���������� 
                              // � ������� + �� �����
    long work_time=0; // ����� ������ ��������

    std::chrono::system_clock::time_point start_work;
    std::chrono::system_clock::time_point start_line_length;

    Checkout* checkouts; // ������ ����
    std::deque<Customer> line; // ������ �������� � �������

    void serve(Customer customer, int checkout_number);

    std::mutex mu;
    std::mutex mu1;

 public:
    Shop();
    Shop(int _checkout_count,
        int _product_processing_time,
        int _max_line_length);
    Shop(const Shop &s);

    void Open();
    void Handle_customer(Customer customer);
    void Close();


    int get_served_customers_count(); //���������� ����������� ��������
    int get_unserved_customers_count(); // ���������� ������������� ��������
    double get_avarage_line_length(); // ������� ����� �������
    double get_avarage_customer_time(); // ������� ����� ���������� ����������
                                        // � ������� + �� �����
    double get_avarage_checkout_work_time(); // ������� ����� ������ �����
    double get_avarage_chechout_downtime(); // ������� ����� ������� �����
    long get_work_time();
};


class Model {
 private:

    int checkout_count; // ���������� ����
    int product_processing_time; // ����� ��������� ������ �� �����
    int max_line_length; // ������������ ����� �������
    double intensity_customer; // ������������� ������ ��������
    double avarage_count_of_products; // ������� ���������� ������� � �������

    Shop shop;

    double theoretical_probability_of_rejection; //����. ���������� ������
    double theoretical_relative_throughput; //����. ���. ���������� �����������
    double theoretical_absolute_throughput; //����. ���. ���������� �����������

    double actual_probability_of_rejection; // ������������ ���������� ������
    double actual_relative_throughput; // �����. ���. ���������� �����������
    double actual_absolute_throughput; // �����. ���. ���������� �����������


    double actual_avarage_count_of_products;
    double actual_intensity_of_customers;
 public:
    Model(int _checkout_count, double _intensity_customer,
        int _product_processing_time, double _avarage_count_of_products,
        int _max_line_length);

    void Run(int time_of_work);
    int get_random_number(double avarage, double standart_deviation);

    double get_theoretical_probability_of_rejection();//����. ���������� ������
    double get_theoretical_relative_throughput();//����. ���. ����. �����������
    double get_theoretical_absolute_throughput();//����. ���. ����. �����������

    double get_actual_probability_of_rejection();//�����. ���������� ������
    double get_actual_relative_throughput(); //�����. �����. ����. �����������
    double get_actual_absolute_throughput(); //�����. ��c. ����. �����������

    int get_served_customers_count(); //���������� ����������� ��������
    int get_unserved_customers_count(); // ���������� ������������� ��������
    double get_avarage_line_length(); // ������� ����� �������
    double get_avarage_customer_time(); // ������� ����� ���������� ����������
                                        // � ������� + �� �����
    double get_avarage_checkout_work_time(); // ������� ����� ������ �����
    double get_avarage_chechout_downtime(); // ������� ����� ������� �����
    long get_work_time();

    double get_actual_avarage_count_of_products();
    double get_actual_intensity_of_customers();
};
