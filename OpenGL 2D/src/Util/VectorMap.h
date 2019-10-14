#pragma once
#ifndef _H_VECTORMAP
#define _H_VECTORMAP

#include <map>
#include <vector>
#include <algorithm>

template <class W, class T>
class VectorMap {
	std::map<W, std::vector<T>> data = std::map<W, std::vector<T>>();
	std::vector<T> list = std::vector<T>();

public:
	bool keepList = false;

	void addElement(const W& weight, const T& element) {
		auto it = data.find(weight);

		if (it != data.end()) {
			data[weight].push_back(element);
		} else {
			// Create a new list
			std::vector<T> batch = std::vector<T>();
			batch.push_back(element);
			data[weight] = batch;
		}

		if (keepList) {
			list.push_back(element);
		}
	}

	void removeElement(const W& index, const T& element) {
		std::vector<T>& batch = data[index];
		batch.erase(remove(batch.begin(), batch.end(), element), batch.end());

		if (keepList) {
			for (auto i = list.begin(); i != list.end(); i++) {
				if (*i == element) {
					list.erase(i);
					break;
				}
			}
		}
	}

	std::vector<T>& get(const W& index){
		return data[index];
	}

	typename std::map<W, std::vector<T>>::const_iterator begin() const{
		return data.begin();
	}

	typename std::map<W, std::vector<T>>::const_iterator end() const{
		return data.end();
	}

	typename std::map<W, std::vector<T>>::iterator begin2() {
		return data.begin();
	}

	typename std::map<W, std::vector<T>>::iterator end2() {
		return data.end();
	}

	std::vector<T>& getList() {
		return list;
	}
};

#endif