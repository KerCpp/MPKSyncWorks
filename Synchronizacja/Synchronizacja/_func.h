#pragma once
#include "_slaves.h"
#include "_kint.h"
#include "mpolaczen.h"
#include "individual.h"
#include "grupa.h"
#include <vector>
#include <iostream>


void wyswietl(std::vector<kint<int> > v, int R);

std::vector<Cgroup> divideIntoGroups(const CconnectionMatrix &matrix);

const individual sync(const CconnectionMatrix &, const std::vector<Cgroup> &);

void save(const individual&);