
#include <iostream>
#include <string>

#include <iostream>
#include <utility>
#include <map>
#include <vector>
#include <type_traits>

template <typename T>
struct is_pair : std::false_type {};

template <typename T, typename U>
struct is_pair<std::pair<T, U>> : std::true_type {};

template <typename T>
constexpr bool is_pair_v = is_pair<T>::value;

template <typename T, typename U = void>
struct is_map : std::false_type {};

template <typename T>
struct is_map<T, std::enable_if_t<
                        is_pair_v< typename std::iterator_traits< typename T::iterator >::value_type > , void
                    > > : std::true_type {};

template <typename T>
constexpr bool is_map_v = is_map<T>::value;


template <typename T>
struct PrintContainer {
    template <typename F = typename std::enable_if_t<is_map_v<std::remove_reference_t<T>>>>
    void print(T& container) {
        std::cout << "map" << std::endl;
    }

    template <typename F = typename std::enable_if_t<not is_map_v<std::remove_reference_t<T>>>>
    void print(T& container) {
        std::cout << "not map" << std::endl;
    }

    PrintContainer(T v) : is_map {is_map_v<std::remove_reference_t<T>>} {
        std::cout << "is_map: " << std::boolalpha << is_map << std::endl;
    }
    bool is_map;
};

int main()
{
    std::vector<int> v;
    v.push_back(1);
    PrintContainer v_pc(v);

    std::map<int, int> p_map;
    p_map[1] = 2;
    PrintContainer m_pc(p_map);

    std::cout << std::boolalpha;
    std::cout << "vector is_map: " << v_pc.is_map << std::endl;
    std::cout << "map is_map: " << m_pc.is_map << std::endl;
}
