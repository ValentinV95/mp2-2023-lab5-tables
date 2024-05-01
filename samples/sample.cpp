#include <iostream>
#include "error.h"
#include "postfix.h"
#include "polynoms.h"

int main()
{
	Postfix p;

	while (true)
	{
		try
		{
			std::cout << "(op:) > ";
			std::string s;
			std::string key;
			std::getline(std::cin, s);
			if (s == "q" || s == "quit") break;

			else if (s == "r" || s == "remove")
			{
				std::cout << "Enter variable name.\n";
				std::getline(std::cin, key);

				while (true)
				{
					std::cout << "1. Unordered table.\n"
						"2. Ordered table.\n"
						"3. Red-black tree.\n"
						"4. Hash table.\n";
					std::getline(std::cin, s);

					switch (s[0])
					{
					case '1':
						p.remove(key, 0);
						break;
					case '2':
						p.remove(key, 1);
						break;
					case '3':
						p.remove(key, 2);
						break;
					case '4':
						p.remove(key, 3);
						break;
					default:
						std::cout << "What?\n";
						continue;
					}

					break;
				}
			}

			else if (s == "h" || s == "help")
			{
				std::cout << "Enter (q)uit to exit program or (h)elp for available features\n"
					"You can enter polynomials of three variables x, y, z like this: xyz+x+y+z\n"
					"The degrees are entered like this: x^4y^4\n"
					"The order of the monomials entered is not important, variables can be presented more than once: xzyxxy+z+x\n"
					"The max degree of variable is " << MAX_MONOM_DEGREE-1 <<
					"\nYou can enter monomial coefficients like a decimal fraction, or in an exponential form: 1.34x, or 1.34e+01x\n"
					"You can access stored polynomials by typing their name\n"
					"To remove a variable, enter (r)emove, then proceed with the instructions\n"
					;
			}

			else
			{
				Polynom pol = p.evaluate(s);
				std::cout << "\nResult: " << pol << std::endl;
				while (true)
				{
					std::cout << "Do you want to save the polynomial? Choose:\n"
						"y. Yes, save\n"
						"n. Don't save.\n";

					std::getline(std::cin, s);

					switch (s[0])
					{
					case 'y':
					case 'Y':
						std::cout << "Enter variable name.\n";
						std::getline(std::cin, key);

						while (true)
						{
							std::cout << "1. Unordered table.\n"
								"2. Ordered table.\n"
								"3. Red-black tree.\n"
								"4. Hash table.\n";
							std::getline(std::cin, s);

							switch (s[0])
							{
							case '1':
								p.insert(key, pol, 0);
								break;
							case '2':
								p.insert(key, pol, 1);
								break;
							case '3':
								p.insert(key, pol, 2);
								break;
							case '4':
								p.insert(key, pol, 3);
								break;
							default:
								std::cout << "What?\n";
								continue;
							}

							break;
						}
					case 'n':
					case 'N':
						break;
					default:
						std::cout << "What?\n";
						continue;
					}

					break;
				}
			}
		}

		catch (std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
	}

	return 0;
}