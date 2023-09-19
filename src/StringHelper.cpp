#include "StringHelper.h"




bool StringHelper::endsWith(const string& target, const string& ending) {
    auto pos = target.rfind(ending);
    return pos == target.length() - ending.length();
}
