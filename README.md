# my_cpp_gadgets
Some useful template functions.

More examples in test_{gadget}.cpp

- Curried function compatitive with all Callables.

        #include "curry.hpp"

        func(1, "good", 2.5);

        auto curried_func = curry(func);
        curried_func(1)("good")(2.5);

- Flip or permute arguments.

        #include "permute.hpp"

        func1(1, "good");
        func2(1, "good", 2.5);

        auto flipped_func1 = flip(func1);
        auto flipped_func2 = flip(func2);
        flipped_func1("good", 1);
        flipped_func2(2.5, "good", 1);

        auto permuted_func2 = permute<1, 0, 2>(func1);
        permuted_func2("good", 1, 2.5);

- Existential type

        #include "existential.hpp"

        struct Cat {
            auto makeSound() {}  
        };
        struct Dog {
            auto makeSound() {}  
        };

        struct Animal { ... };

        Cat cat;
        Dog dog;
        vector<Animal> animal_vec;
        animal_vec.push_back(cat);
        animal_vec.push_back(dog);
        for (auto&& ani: animal_vec) {
            ani.makeSound();
        }

        // -----

        struct Stage1 { 
            Convertable convert(); 
        };
        struct Stage2 {
            Convertable convert();
        };
        struct Stage3 { 
            Convertable convert();
        };
        Stage1::convert() { return Stage2{}; }
        Stage2::convert() { return Stage3{}; }
        Stage3::convert() { return Stage1{}; }

        vector<Convertable> stages{Stage1{}, Stage2{}, Stage3{}};
        for (auto& stg: stages) {
            stg = stg.convert(); // next stage (another type)
        }

        // elements in stages: 
        // [Stage2{}, Stage3{}, Stage1{}]

- Expansion for

        #include "expansion_for.hpp"

        for_<10>([](auto i) { // force expansion
            cout << i << endl;
        }); 

        // would be expand to
        // cout << 0 << endl;
        // cout << 1 << endl;
        // cout << 2 << endl;
        // cout << 3 << endl;
        // ...
        // cout << 9 << endl;

