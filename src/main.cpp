#include <iostream>
#include <cstdio>
#include <vector>

#include "util/types.h"

#if 1
#define center 0.080829, 0.14, 0.0571548
#else
#define center 0, 0, 0
#endif
#define name freq
#define inc 25
#define unit Hz

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

struct tableEntry {
    v3 actual;
	v3 locate;

	tableEntry() : actual(), locate() {}

	tableEntry(FILE * file) {
		fscanf(file, "%lf, %lf, %lf, %lf, %lf, %lf\n",
			   &actual.x, &actual.y, &actual.z,
			   &locate.x, &locate.y, &locate.z);
	}

	int writeToFile(FILE * file) {
		return fprintf(file, "%lf, %lf, %lf, %lf, %lf, %lf\n",
			   actual.x, actual.y, actual.z,
			   locate.x, locate.y, locate.z);
	}

	bool operator==(tableEntry& rhs) {
		return (actual == rhs.actual);
	}
};

int main(int argc, char ** argv) {
	FILE * inFile = fopen(argv[1], "r");
	FILE * outFile = fopen(argv[2], "w");
	tableEntry curEntry(inFile), newEntry;
	u64 lines;

	std::vector<tableEntry> entries;

	while(!feof(inFile)) {
		newEntry = tableEntry(inFile);
#if 0
		if(newEntry == curEntry) {
			// NOOP lets read the next entry
		} else {
#endif
			if(curEntry.locate.norm() < 30) {
				curEntry.writeToFile(outFile);
				entries.push_back(curEntry);
			}
#if 0
		}
#endif
		if(lines++ % 10000 == 0) {
			std::cout << "\rlines: " << lines << std::flush;
		}

		curEntry = newEntry;
	}

	std::cout << "\rlines: " << lines << std::flush << std::endl;

	std::vector<std::vector<tableEntry>> rEntries;

	for(u64 i = 0; i < 1024; i++) {
		rEntries.push_back(std::vector<tableEntry>());
	}

	u64 f = 0;
	u64 counter = 0;

	for(auto entry : entries) {
		entry.locate -= v3(center);
		entry.actual -= v3(center);

		if(counter++ % (36*36) == 0) {
			f++;
		}
		rEntries[f - 1].push_back(entry);

//		std::cout << entry.actual << std::endl;
//		std::cout << entry.locate << std::endl;
	}

	f64 name = 500;

	for(auto entries : rEntries) {
		if(entries.size() == 0)
			break;

		f64 mean = 0, sigma = 0, value = 0;

		for(auto entry : entries) {
			value = acos(entry.actual.dotP(entry.locate) / (entry.actual.norm() * entry.locate.norm()));
			if(!isnan(value)) {
				mean += value;
				sigma += value * value;
			}
		}

		mean /= entries.size();
		sigma /= entries.size();
		sigma /= entries.size() - 1;
		sigma = sqrt(sigma);


		std::cout << name << ", " << (mean / (2 * M_PI)) * 360 << ", ";
#if 0
		std::cout << TOSTRING(name) << ": " << name << TOSTRING(unit) << std::endl;
		std::cout << "mean: " << (mean / (2 * M_PI)) * 360 << std::endl;
		std::cout << "sigma1: " << (sigma / (2 * M_PI)) * 360 << std::endl;
#endif

		sigma = 0;
		f64 diff = 0;

		for(auto entry : entries) {
			value = acos(entry.actual.dotP(entry.locate) / (entry.actual.norm() * entry.locate.norm()));
			if(!isnan(value)) {
			diff = value - mean;
			diff *= diff;
			sigma += diff;
			}
		}

		name += inc;

		sigma /= entries.size();
		sigma /= entries.size() - 1;
		sigma = sqrt(sigma);
#if 0
		std::cout << "sigma2: " << (sigma / (2 * M_PI)) * 360 << std::endl;
#endif
		std::cout << (sigma / (2 * M_PI)) * 360  << std::endl;
	}


	f64 mean = 0, sigma = 0, value = 0;

	for(auto entry : entries) {
		entry.locate -= v3(center);
		entry.actual -= v3(center);

		value = acos(entry.actual.dotP(entry.locate) / (entry.actual.norm() * entry.locate.norm()));
		if(!isnan(value)) {
			mean += value;
			sigma += value * value;
		}
	}

	mean /= entries.size();
	sigma /= entries.size();
	sigma /= entries.size() - 1;
	sigma = sqrt(sigma);

	std::cout << "total: " << std::endl;
	std::cout << "mean: " << (mean / (2 * M_PI)) * 360 << std::endl;
	std::cout << "sigma1: " << (sigma / (2 * M_PI)) * 360 << std::endl;

	sigma = 0;
	f64 diff = 0;

	for(auto entry : entries) {
		value = acos(entry.actual.dotP(entry.locate) / (entry.actual.norm() * entry.locate.norm()));
		if(!isnan(value)) {
			diff = value - mean;
			diff *= diff;
			sigma += diff;
		}
	}

	sigma /= entries.size();
	sigma /= entries.size() - 1;
	sigma = sqrt(sigma);

	std::cout << "sigma2: " << (sigma / (2 * M_PI)) * 360 << std::endl;
}
