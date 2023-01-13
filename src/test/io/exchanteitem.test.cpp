#include "exchangeItem.hpp"
#include "up11.h"

UP_SUITE_BEGIN(exchangeItem);

UP_TEST(setValue)
{
    ExchangeItem e({"Test"});
    e["Test"] = "Hello";
    UP_ASSERT(e["Test"].compare("Hello") == 0);
}

UP_TEST(setProperties)
{
    ExchangeItem e({"Test", "Test2"});
    e["Test"]="Hello";
    e["Test2"]="World";
    e.setProperties({"Test", "Test3"});
    UP_ASSERT_EQUAL(e["Test"], "Hello");
    UP_ASSERT_EQUAL(e["Test3"], "");
}

UP_TEST(outOfRange)
{
    UP_ASSERT_EXCEPTION(out_of_range, []{
        ExchangeItem e({"Test"});
        // Devrait renvoyer l'exception de type out_of_range
        e["Tete"]="Hello";
    });
}

UP_SUITE_END();