#include "characterBuilder.h"
#include "character.h"
#include <vector>

using  namespace std;

characterBuilder::characterBuilder()
{
	toBuild = new character();
}


characterBuilder::~characterBuilder()
{
}



void characterBuilder::generateAbilities() {

	vector<int> abUnsorted=vector<int>();

	for (int i = 0; i < 6; i++) {
		abUnsorted.push_back(character::getMaxRollSum(6, 4));
	}

	std::sort(abUnsorted.begin(), abUnsorted.end());
	
	character::abilList abls = assignAbilities(abUnsorted);

	toBuild->setAbilities(abls);

}