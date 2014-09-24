/**
 * Copyright (c) 2014 Daniel Wiberg
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#pragma once

#include "glm/glm.hpp"
#include "Mesh.hpp"

#include <vector>

namespace slg {

  bool loadObj(const char * filename,
               std::vector<glm::vec3> & vertices,
               std::vector<glm::vec2> & uvs,
               std::vector<glm::vec3> & normals);

  void computeTangentBasis(std::vector<glm::vec3> const& vertices,
                           std::vector<glm::vec2> const& uvs,
                           std::vector<glm::vec3> const& normals,
                           std::vector<glm::vec3> & tangents,
                           std::vector<glm::vec3> & bitangents);

   void calculateIndex(std::vector<glm::vec3> const& inVertices,
                       std::vector<glm::vec2> const& inUvs,
                       std::vector<glm::vec3> const& inNormals,
                       std::vector<unsigned short> & outIndices,
                       std::vector<glm::vec3> & outVertices,
                       std::vector<glm::vec2> & outUvs,
                       std::vector<glm::vec3> & outNormals);


  void calculateIndex(std::vector<glm::vec3> const& inVertices,
                      std::vector<glm::vec2> const& inUvs,
                      std::vector<glm::vec3> const& inNormals,
                      std::vector<glm::vec3> const& inTangents,
                      std::vector<glm::vec3> const& inBitangents,
                      std::vector<unsigned short> & outIndices,
                      std::vector<glm::vec3> & outVertices,
                      std::vector<glm::vec2> & outUvs,
                      std::vector<glm::vec3> & outNormals,
                      std::vector<glm::vec3> & outTangents,
                      std::vector<glm::vec3> & outBitangents);

  void createQuad(Mesh & mesh, bool inClipSpace);

  inline void pushTriangle(std::vector<unsigned short> & data, unsigned short a, unsigned short b, unsigned short c)
  {
    data.push_back(a);
    data.push_back(b);
    data.push_back(c);
  }

}
