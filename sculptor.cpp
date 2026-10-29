#include "sculptor.h"

#include <fstream>


Sculptor::Sculptor(int _nx, int _ny, int _nz) {
    nx = _nx;
    ny = _ny;
    nz = _nz;

    v = new Voxel**[nx];

    for (int i = 0; i < nx; i++) {
        v[i] = new Voxel*[ny];

        for (int j = 0; j < ny; j++) {
            v[i][j] = new Voxel[nz];

            for (int k = 0; k < nz; k++) {
                v[i][j][k].r = 0;
                v[i][j][k].g = 0;
                v[i][j][k].b = 0;
                v[i][j][k].a = 0;
                v[i][j][k].show = false;
            }
        }
    }

    r = 0;
    g = 0;
    b = 0;
    a = 1;
}

Sculptor::~Sculptor() {
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            delete[] v[i][j];
        }

        delete[] v[i];
    }

    delete[] v;
}

void Sculptor::setColor(float r, float g, float b, float alpha) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = alpha;
}

void Sculptor::putVoxel(int x, int y, int z) {
    if (x < 0 || x >= nx ||
        y < 0 || y >= ny ||
        z < 0 || z >= nz) {
        return;
    }

    v[x][y][z].show = true;
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;
}

void Sculptor::cutVoxel(int x, int y, int z) {
    if (x < 0 || x >= nx ||
        y < 0 || y >= ny ||
        z < 0 || z >= nz) {
        return;
    }

    v[x][y][z].show = false;
}

void Sculptor::putBox(int x0, int x1,
                      int y0, int y1,
                      int z0, int z1) {
    for (int i = x0; i <= x1; i++) {
        for (int j = y0; j <= y1; j++) {
            for (int k = z0; k <= z1; k++) {
                putVoxel(i, j, k);
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1,
                      int y0, int y1,
                      int z0, int z1) {
    for (int i = x0; i <= x1; i++) {
        for (int j = y0; j <= y1; j++) {
            for (int k = z0; k <= z1; k++) {
                cutVoxel(i, j, k);
            }
        }
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter,
                         int radius) {
    for (int x = xcenter - radius; x <= xcenter + radius; x++) {
        for (int y = ycenter - radius; y <= ycenter + radius; y++) {
            for (int z = zcenter - radius; z <= zcenter + radius; z++) {

                int dx = x - xcenter;
                int dy = y - ycenter;
                int dz = z - zcenter;

                if (dx * dx + dy * dy + dz * dz <= radius * radius) {
                    putVoxel(x, y, z);
                }
            }
        }
    }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter,
                         int radius) {
    for (int x = xcenter - radius; x <= xcenter + radius; x++) {
        for (int y = ycenter - radius; y <= ycenter + radius; y++) {
            for (int z = zcenter - radius; z <= zcenter + radius; z++) {

                int dx = x - xcenter;
                int dy = y - ycenter;
                int dz = z - zcenter;

                if (dx * dx + dy * dy + dz * dz <= radius * radius) {
                    cutVoxel(x, y, z);
                }
            }
        }
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter,
                            int rx, int ry, int rz) {
    if (rx <= 0 || ry <= 0 || rz <= 0) {
        return;
    }

    for (int x = xcenter - rx; x <= xcenter + rx; x++) {
        for (int y = ycenter - ry; y <= ycenter + ry; y++) {
            for (int z = zcenter - rz; z <= zcenter + rz; z++) {

                float dx = float(x - xcenter) / rx;
                float dy = float(y - ycenter) / ry;
                float dz = float(z - zcenter) / rz;

                if (dx * dx + dy * dy + dz * dz <= 1.0f) {
                    putVoxel(x, y, z);
                }
            }
        }
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter,
                            int rx, int ry, int rz) {
    if (rx <= 0 || ry <= 0 || rz <= 0) {
        return;
    }

    for (int x = xcenter - rx; x <= xcenter + rx; x++) {
        for (int y = ycenter - ry; y <= ycenter + ry; y++) {
            for (int z = zcenter - rz; z <= zcenter + rz; z++) {

                float dx = float(x - xcenter) / rx;
                float dy = float(y - ycenter) / ry;
                float dz = float(z - zcenter) / rz;

                if (dx * dx + dy * dy + dz * dz <= 1.0f) {
                    cutVoxel(x, y, z);
                }
            }
        }
    }
}
void Sculptor::writeOFF(const char* filename) {
  std::ofstream fout;
  int nvertices = 0, nfaces = 0, nvoxels = 0;
  fout.open(filename);

  if (!fout.is_open()) {
    exit(1);
  }
  // laco triplo para contar os
  // voxels ativos marcados com show = true

  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
        for (int k = 0; k < nz; k++) {
            if (v[i][j][k].show) {
                nvoxels++;
            }
        }
    }
}

  nvertices = 8 * nvoxels;
  nfaces = 6 * nvoxels;

  fout << "OFF\n";
  fout << nvertices << " " << nfaces << " 0\n";

  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
        for (int k = 0; k < nz; k++) {
            if (v[i][j][k].show) {
                fout << i     << " " << j     << " " << k     << "\n";
                fout << i + 1 << " " << j     << " " << k     << "\n";
                fout << i + 1 << " " << j + 1 << " " << k     << "\n";
                fout << i     << " " << j + 1 << " " << k     << "\n";
                fout << i     << " " << j     << " " << k + 1 << "\n";
                fout << i + 1 << " " << j     << " " << k + 1 << "\n";
                fout << i + 1 << " " << j + 1 << " " << k + 1 << "\n";
                fout << i     << " " << j + 1 << " " << k + 1 << "\n";
            }
        }
    }
}

int voxelIndex = 0;

for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
        for (int k = 0; k < nz; k++) {
            if (v[i][j][k].show) {
                int base = 8 * voxelIndex;

                fout << "4 " << base     << " " << base + 3
                     << " " << base + 2 << " " << base + 1
                     << " " << v[i][j][k].r
                     << " " << v[i][j][k].g
                     << " " << v[i][j][k].b
                     << " " << v[i][j][k].a << "\n";

                fout << "4 " << base + 4 << " " << base + 5
                     << " " << base + 6 << " " << base + 7
                     << " " << v[i][j][k].r
                     << " " << v[i][j][k].g
                     << " " << v[i][j][k].b
                     << " " << v[i][j][k].a << "\n";

                fout << "4 " << base     << " " << base + 1
                     << " " << base + 5 << " " << base + 4
                     << " " << v[i][j][k].r
                     << " " << v[i][j][k].g
                     << " " << v[i][j][k].b
                     << " " << v[i][j][k].a << "\n";

                fout << "4 " << base + 1 << " " << base + 2
                     << " " << base + 6 << " " << base + 5
                     << " " << v[i][j][k].r
                     << " " << v[i][j][k].g
                     << " " << v[i][j][k].b
                     << " " << v[i][j][k].a << "\n";

                fout << "4 " << base + 2 << " " << base + 3
                     << " " << base + 7 << " " << base + 6
                     << " " << v[i][j][k].r
                     << " " << v[i][j][k].g
                     << " " << v[i][j][k].b
                     << " " << v[i][j][k].a << "\n";

                fout << "4 " << base + 3 << " " << base
                     << " " << base + 4 << " " << base + 7
                     << " " << v[i][j][k].r
                     << " " << v[i][j][k].g
                     << " " << v[i][j][k].b
                     << " " << v[i][j][k].a << "\n";

                voxelIndex++;
            }
        }
    }
}
  fout.close();
}