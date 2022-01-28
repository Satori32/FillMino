#include <iostream>
#include <vector>
#include <cstdint>
#include <tuple>
#include <algorithm>

typedef std::vector<std::vector<std::uint8_t>> DType;
typedef std::vector<DType> Mino;
typedef std::vector<Mino> Minos;

typedef std::vector<DType> RType;

bool SetMino(DType& M, const DType& D, std::size_t X, std::size_t Y, std::uintmax_t C) {

	if (D.size() + Y > M.size()) return false;
	if (D[0].size() + X > M[0].size()) return false;


	for (std::size_t i = 0; i < D.size(); i++) {
		for (std::size_t j = 0; j < D[i].size(); j++) {
			if (D[i][j] != 0) {
				if (M[i + Y][j + X] != 0) {
					return false;
				}
			}
		}
	}

	for (std::size_t i = 0; i < D.size(); i++) {
		for (std::size_t j = 0; j < D[i].size(); j++) {
			if (D[i][j] != 0) {
				if (M[i + Y][j + X] == 0) {
					M[i + Y][j + X] = C;
				}
			}
		}
	}
	return true;
}

bool IsFilled(const DType& D, std::size_t C=0) {
	for (auto& oo : D) {
		for (auto& o : oo) {
			if (o == 0) {
				if (C == 0) {
					return false;
				}
				else {
					C--;
				}
			}
		}
	}
	return true;
}

RType MakeHoge(const Mino& D, std::size_t W, std::size_t H, std::size_t X, std::size_t Y) {

	RType R;
	DType Map;

	std::uintmax_t C = 1;



	//std::tuple<int, int, DType> SI;
	std::vector<std::tuple<int, int, int, DType>> SI;

	SI.push_back({ 0,0,0,Map });

	Map.resize(H);
	for (auto& o : Map) { o.resize(W); }


	for (std::size_t i = 0; i < H; i++) {
		for (std::size_t j = 0; j < W; j++) {
			for (std::size_t h = 0; h < D.size(); h++) {
				if (SetMino(Map, D[h], j, i, C % 256)) {
					C++;
					SI.push_back({ j,i,h,Map });

					if (IsFilled(Map)) {
						R.push_back(Map);
					}
				}
			}
		}
	}

	return R;

}

	

bool Show(const RType& R){

	for (auto& ooo : R) {
		for (auto& oo : ooo) {
			for (auto& o : oo) {
				std::cout <<(int) o << ",";
			}
			std::cout<<std::endl;
		}
		std::cout<<std::endl;
	}
		std::cout<<std::endl;

	return true;

}

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
			{1,1},
			{0,1},
			{0,1},
			{0,0}
		},
		{
			{0,0},
			{1,0},
			{1,0},
			{1,1},
		},
	};

	RType R = MakeHoge(M, 4,4 , 2, 4);

	std::sort(R.begin(), R.end());
	R.erase(std::unique(R.begin(), R.end()),R.end());

	Show(R);

	return 0;


}
