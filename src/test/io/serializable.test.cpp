#include "serializable.test.hpp"

UP_SUITE_BEGIN(serializable);


UP_TEST(implementation)
{
    
    MockSerializable s("Tiberghien","Mathias");
    ExchangeItem e = s.to_exchangeItem();
    UP_ASSERT_EQUAL("Tiberghien", e["Nom"]);
    UP_ASSERT_EQUAL("Mathias", e["Prenom"]);
    e["Prenom"]="Thomas";
    s.from_exchangeItem(e);
    UP_ASSERT_EQUAL("Thomas", s.getPrenom());
    UP_ASSERT_EQUAL("Tiberghien", s.getNom());
}



UP_SUITE_END();