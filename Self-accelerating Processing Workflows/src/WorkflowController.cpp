#include <iostream>
#include <Constants.h>
#include <WorkflowController.h>

#include <ComputationalModel.h>
#include <iostream>
#include <chrono>
#include <time.h>
#include <windows.h>
#include <thread>
#include <functional>
#include <list>
#include <mutex>

using namespace std;

list<ComputationalModel*> registeredModels;

WorkflowController::WorkflowController() {}
WorkflowController::~WorkflowController() {}

std::mutex mtx;

void WorkflowController::launchBenchmarkUpdater()
{
  std::thread([=]()
  {
    while (true)
    {
      reviseAllBenchmarks();
      auto x = std::chrono::steady_clock::now() + std::chrono::milliseconds(REVISE_PERIOD);
      std::this_thread::sleep_until(x);
    }
  }).detach();
}

void WorkflowController::reviseAllBenchmarks()
{
  std::cout << "To do" << std::endl;
}

void WorkflowController::updateArrayAdditionBenchmark()
{
  std::cout << "To do" << std::endl;
}

void WorkflowController::registerModel(ComputationalModel * cModel) {
    registeredModels.push_back(cModel);
}

void WorkflowController::updateCPUTime(ComputationalModel* cModel) {
    mtx.lock();
    float newMean = (float)cModel->clocks.CPU / REVISE_COUNT;
    cModel->clocks.CPU = 0;
    cout << newMean << "," << cModel->clocks.GPUmean << endl << endl;
    cModel->countS = 0;
    if (newMean > cModel->clocks.GPUmean) {
        cModel->setProcessor(1);
    }
    cModel->clocks.CPUmean = newMean;
    if (cModel->countL > RESET_COUNT) {
        cModel->clocks = { 0,0,0.0,0.0 };
        cModel->countL = 0;
        cModel->countS = 0;
    }
    mtx.unlock();
}

void WorkflowController::updateGPUTime(ComputationalModel * cModel) {
    mtx.lock();
    float newMean = (float)cModel->clocks.GPU / REVISE_COUNT;
    cModel->clocks.GPU = 0;
    cout << cModel->clocks.CPUmean << "," << newMean << endl << endl;
    cModel->countS = 0;
    if (newMean > cModel->clocks.CPUmean) {
        cModel->setProcessor(0);
    }
    cModel->clocks.GPUmean = newMean;
    if (cModel->countL > RESET_COUNT) {
        cModel->clocks = { 0,0,0.0,0.0 };
        cModel->countL = 0;
        cModel->countS = 0;
    }
    mtx.unlock();
}
