#pragma once

#include "Core/Application.h"

class Triangle : public Application
{ 
protected:

  virtual void init() override;
  virtual void appLoop() override;

private:

  Program mProgram;
  VertexArray mVertexArray;
};

