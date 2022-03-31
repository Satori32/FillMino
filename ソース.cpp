#include <iostream>
#include <vector>
#include <cstdint>
#include <tuple>
#include <algorithm>
#include <limits>

typedef std::vector<std::vector<std::uint8_t>> DType;
typedef std::vector<DType> Mino;
typedef std::vector<Mino> Minos;

typedef std::vector<DType> RType;

bool Show(const RType& R){

	for (auto& ooo : R) {
		for (auto& oo : ooo) {
			for (auto& o : oo) {
				std::cout <<(int) o << ",\t";
			}
			std::cout<<std::endl;
		}
		std::cout<<std::endl;
	}
		std::cout<<std::endl;

	return true;

}
bool SetMino(DType& M, const DType& D, std::size_t X, std::size_t Y, std::uintmax_t C) {

	std::size_t PX = std::numeric_limits<std::size_t>::max();
	std::size_t PY = std::numeric_limits<std::size_t>::max();

	for (std::size_t i = 0; i < D.size(); i++) {
		for (std::size_t j = 0; j < D[i].size(); j++) {
			if (D[i][j] != 0) {
				if (PX > j) { PX = j; }
				if (PY > i) { PY = i; }
			}
		}
	}

	if ((D.size() + Y)-PY > M.size()) return false;
	if ((D[0].size() + X)-PX > M[0].size()) return false;

	for (std::size_t i = PY; i < D.size(); i++) {
		for (std::size_t j = PX; j < D[i].size(); j++) {
			if (D[i][j] != 0) {
				if (M[i + Y-PY][j + X-PX] != 0) {
					return false;
				}
			}
		}
	}

	for (std::size_t i = PY; i < D.size(); i++) {
		for (std::size_t j = PX; j < D[i].size(); j++) {
			if (D[i][j] != 0) {
				if (M[i + Y-PY][j + X-PX] == 0) {
					M[i + Y-PY][j + X-PX] = C;
				}
			}
		}
	}
	return true;
}
bool UnSetMino(DType& M, const DType& D, std::size_t X, std::size_t Y) {

	std::size_t PX = std::numeric_limits<std::size_t>::max();
	std::size_t PY = std::numeric_limits<std::size_t>::max();

	for (std::size_t i = 0; i < D.size(); i++) {
		for (std::size_t j = 0; j < D[i].size(); j++) {
			if (D[i][j] != 0) {
				if (PX > j) { PX = j; }
				if (PY > i) { PY = i; }
			}
		}
	}

	for (std::size_t i = PY; i < D.size(); i++) {
		for (std::size_t j = PX; j < D[i].size(); j++) {
			if (D[i][j] != 0) {
				if (M[i + Y-PY][j + X-PX] == 0) {
					return false;
				}
			}
		}
	}

	for (std::size_t i = PY; i < D.size(); i++) {
		for (std::size_t j = PX; j < D[i].size(); j++) {
			if (D[i][j] != 0) {
				if (M[i + Y - PY][j + X - PX] != 0) {
					M[i + Y - PY][j + X - PX] = 0;
				}
			}
		}
	}

	return true;

}
bool IsFilled(const DType& D, std::size_t C=0) {
	for (auto& oo : D) {
		for (auto& o : oo) {
			if (o == C) {
				return false;
			}
		}
	}
	return true;
}

typedef std::tuple<DType, std::size_t, std::size_t, std::size_t> Data;
typedef std::vector<Data> St;
RType MakeHoge(const Mino& D, std::size_t W, std::size_t H) {

	RType R;
	DType M;
	
	M.resize(H);
	for (auto& o : M) { o.resize(W); }
	
	std::uint8_t C = 1;

	St V;

	std::size_t i = 0;
	std::size_t j = 0;
	std::size_t k = 0;

	bool F = false;
	V.push_back({M,0,0,0});
	while (V.size() > 0) {
		if (V.size()) {
			auto& X = V.back();
			M = std::get<0>(X);
			i = std::get<1>(X);
			j = std::get<2>(X);
			k = std::get<3>(X);
			V.pop_back();
		}
		//		for (std::size_t Z = 0; Z < D.size(); Z++) {
		for (i; i < H; i++) {
			for (j; j < W; j++) {
				for (k; k < D.size(); k++) {

					if (SetMino(M, D[k], j, i, C)) {
						C++;
						if (!C) { C++; }
						if (IsFilled(M)) {
							R.push_back(M);
						}
						else {
							V.push_back({ M,i,j,k + 1 });
							UnSetMino(M, D[k], j, i);
						}
					}

				}
				if (k >= D.size())k = 0;
			}
			if (j >= W) j = 0;
		}
		if (i >= H)i = 0;

		//		}
	}

	return R;

}

	
/**/



int main() {

	Mino M{
		/*{
			{1,1,1,1,1,1},
			{0,1,0,0,0,0},
			{0,1,1,1,1,0},
			{0,1,0,0,0,0},
			{0,1,0,0,0,0},
			{0,1,0,0,0,0},
		},
		*/


		{
			{0,0},
			{0,1},
			{0,1},
			{1,1}
		},		{
			{1,1},
			{1,0},
			{1,0},
			{0,0},
		},
	};
	{

		RType R = MakeHoge(M, 6, 8);

		std::sort(R.begin(), R.end());
		R.erase(std::unique(R.begin(), R.end()), R.end());

		Show(R);
	}
	/** /{

		RType R = MakeHoge(M, 8, 8);//this is heavy, can't arrive answer?

		std::sort(R.begin(), R.end());
		R.erase(std::unique(R.begin(), R.end()), R.end());

		Show(R);
	}
	/**/
	return 0;


}
