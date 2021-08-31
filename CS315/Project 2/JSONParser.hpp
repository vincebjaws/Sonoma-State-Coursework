#ifndef LAB01_2_TAGPARSER_HPP
#define LAB01_2_TAGPARSER_HPP

#include <vector>
#include "JSONToken.hpp"
#include "JSONTokenizer.hpp"
#include "Pair.hpp"
#include "EntityInstance.hpp"
#include "Entity.hpp"

class JSONParser {
public:
    JSONParser(JSONTokenizer &tokenizer);
    Pair parseAPair();
    EntityInstance parseJSONObject();
    Entity parseJSONEntity();

private:
    JSONTokenizer &tokenizer;
};

#endif //LAB01_2_TAGPARSER_HPP
