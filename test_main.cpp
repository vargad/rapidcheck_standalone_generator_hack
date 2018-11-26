// 2018 Daniel Varga (vargad88@gmail.com)

#include <iostream>

#include <rapidcheck.h>

int main()
{
    rc::gen::detail::Recipe recipe;
    recipe.random = rc::Random(time(nullptr));
    rc::gen::detail::ExecHandler execHandler(recipe);
    rc::detail::ImplicitParam<rc::gen::detail::param::CurrentHandler> fakeHandler(&execHandler);
    recipe.size = rc::kNominalSize;
    std::cout << *rc::gen::arbitrary<int>() << std::endl;
    return 0;
}

