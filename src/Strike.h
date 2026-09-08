#pragma once
#include "Individual.h"

struct Strike{
    Individual** participatingIndividuals;
    int numParticipatingIndividuals;

    Individual** supportingIndividuals;
    int numSupportingIndividuals;
};
