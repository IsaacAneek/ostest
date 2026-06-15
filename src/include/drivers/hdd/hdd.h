#ifndef DRIVERS_HDD_HDD_H_
#define DRIVERS_HDD_HDD_H_

#include "inlineasm/inlineasm.h"
#include "drivers/video/vga.h"

void select_master_ATA_device();
void wait_for_ATA_device();
read_sectors_LBA(uint32_t LBA, uint8_t sector_count, uint16_t* buffer);
void init_ATA_HDD();

#endif // DRIVERS_HDD_HDD_H_