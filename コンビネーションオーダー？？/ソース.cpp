#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <limits>
#include <numeric>

template<class UInt>
std::vector<UInt> PrimeFacterlizer(UInt N) {

	std::vector<UInt> R;
	for (UInt i = 2; i <= N; i++) {
		if (N % i == 0) {
			R.push_back(i);
			N /= i;
			i--;
		}
	}

	return R;
}

template<class UInt>
std::pair<UInt, UInt> Denomi(UInt A, UInt B) {
	auto X = PrimeFacterlizer(A);
	auto Y = PrimeFacterlizer(B);

	for (std::size_t i = 0; i < X.size(); i++) {
		auto it = std::find(Y.begin(), Y.end(), X[i]);
		if (it != Y.end()) {
			*it = 1;
			X[i] = 1;
		}
	}

	UInt RA = 1;
	for (auto& o : X) {
		RA *= o;
	}
	UInt RB = 1;
	for (auto& o : Y) {
		RB *= o;
	}

	return  { RA,RB };
}

template<class UInt>
UInt Combination(UInt N, UInt r,UInt DenomiLimit) {

	UInt X = 1;
	UInt Y = 1;
	for (UInt i = 0; i <r; i++) {
		X *= (N - i);
		Y *= (r - i);

		UInt Z = 1;

		if (X > DenomiLimit) {
			do {
				X /= Z;
				Y /= Z;
			
			} while ((Z = std::gcd(X, Y)) != 1);
			
		}
	}

	return X / Y;
}
/** /
template<class UInt>
UInt Combination(UInt N, UInt r,UInt DenomiLimit) {

	UInt X = 1;
	UInt Y = 1;
	for (UInt i = 0; i <r; i++) {
		X *= (N - i);
		Y *= (r - i);

		if (X > DenomiLimit) {
			auto Z = Denomi(X, Y);
			X = Z.first;
			Y = Z.second;
		}
	}

	return X / Y;
}
/**/
int main() {
	std::uintmax_t N = 58;
	std::uintmax_t r = 30;
	auto X = Combination(N, r, std::numeric_limits<std::uintmax_t>::max()/1000);

	std::cout << X << std::endl;

	return 0;
}