#include <iostream>

#include "buried_common.h"
#include "buried_core.h"
#include "include/buried.h"
#include "report/buried_report.h"


using namespace std;

extern "C" {
Buried *Buried_Create(const char *work_dir) {
  if (!work_dir) {
    return nullptr;
  }

  return new Buried(work_dir);
}

void Buried_Destroy(Buried *buried) {
  if (buried) {
    delete buried;
  }
}

int32_t Buried_Start(Buried *buried, BuriedConfig *config) {
  if (!buried || !config) {
    return 1;
  }
  Buried::Config buried_config;
  if (config->host) {
    buried_config.host = config->host;
  }
  return buried->Start(buried_config);
}

int32_t Buried_Report(Buried *buried, const char *title, const char *data,
                      uint32_t priority) {
  if (!buried || !title || !data) {
    return -1;
  }
  return buried->Report(title, data, priority);
}
}