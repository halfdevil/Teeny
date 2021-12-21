#pragma once

#include "Core/Application.h"

class Cube : public Application
{ 
public:

  Cube();

protected:

  virtual void init() override;
  virtual void appLoop() override;

private:

  Program mProgram;
  VertexArray mVertexArray;
  Buffer mPerFrameDataBuffer;
  RasterizationState mRasterizationState;
};

