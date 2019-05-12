/*************************************************************************
 * Copyright (c) 2014 Zhang Dongdong
 * All rights reserved.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
**************************************************************************/
#ifndef KDTREE_H
#define KDTREE_H
/*
Szymon Rusinkiewicz
Princeton University

KDtree.h
A K-D tree for points, with limited capabilities (find nearest point to 
a given point, or to a ray). 

Note that in order to be generic, this *doesn't* use Vecs and the like...
*/

#include <vector>

class KDtree {
private:
	class Node;
	Node *root;
	void build(const float *ptlist, size_t n);

public:
	// Compatibility function for closest-compatible-point searches
	struct CompatFunc
	{
		virtual bool operator () (const float *p) const = 0;
		virtual ~CompatFunc() {}  // To make the compiler shut up
	};

	// Constructor from an array of points
	KDtree(const float *ptlist, size_t n)
		{ build(ptlist, n); }

	// Constructor from a vector of points
	template <class T> KDtree(const std::vector<T> &v)
		{ build((const float *) &v[0], v.size()); }

	// Destructor - recursively frees the tree
	~KDtree();

	// The queries: returns closest point to a point or a ray,
	// provided it's within sqrt(maxdist2) and is compatible
	const float *closest_to_pt(const float *p,
				   float maxdist2 = 0.0f,
				   const CompatFunc *iscompat = NULL) const;
	const float *closest_to_ray(const float *p, const float *dir,
				    float maxdist2 = 0.0f,
				    const CompatFunc *iscompat = NULL) const;

	// Find the k nearest neighbors
	void find_k_closest_to_pt(std::vector<const float *> &knn,
				  int k,
				  const float *p,
				  float maxdist2 = 0.0f,
				  const CompatFunc *iscompat = NULL) const;
};

#endif
