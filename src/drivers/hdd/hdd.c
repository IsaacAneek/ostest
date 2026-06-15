#include "inlineasm/inlineasm.h"
#include "drivers/video/vga.h"
#include "drivers/hdd/hdd.h"

// https://thejat.in/learn/real-mode-disk-operations-using-ataatapi

#define BSY 7
#define DDRY 6
#define DRQ 4
#define PRIMARY_ATA_SECTOR_NUMBER 0x1F3
#define PRIMARY_ATA_CYLINDER_LOW 0x1F4
#define PRIMARY_ATA_CYLINDER_HIGH 0x1F5
#define PRIMARY_ATA_SECTOR_COUNT 0x1F2
#define PRIMARY_ATA_COMMAND_AND_STATUS 0x1F7
#define READ_SECTOR_COMMAND 0x20
#define PRIMARY_ATA_DATA 0x1F0

void select_master_ATA_device()
{
    // Select Master device, bit 6 set for LBA mode
    // 0xA0 for master device
    outb(0x1F6, 0xA0);
}

void wait_for_ATA_device()
{
    uint8_t status = inb(PRIMARY_ATA_COMMAND_AND_STATUS);
    // wait for BSY and DRQ bit to set
    while (!(status & (1 << BSY)))
    {
        status = inb(PRIMARY_ATA_COMMAND_AND_STATUS);
    }
    while (!(status & (1 << DRQ)))
    {
        status = inb(PRIMARY_ATA_COMMAND_AND_STATUS);
    }

    // if((status & (1 << DRQ)) == 0) {
    //     puts_vga("Device not present");
    //     return;
    // }
}

read_sectors_LBA(uint32_t LBA, uint8_t sector_count, uint16_t *buffer)
{
    uint8_t lba_low_byte = LBA & 0x0FF;
    uint8_t lba_mid_byte = (LBA >> 8) & 0x0FF;
    uint8_t lba_high_byte = (LBA >> 16) & 0x0FF;
    outb(PRIMARY_ATA_SECTOR_NUMBER, lba_low_byte);
    outb(PRIMARY_ATA_CYLINDER_LOW, lba_mid_byte);
    outb(PRIMARY_ATA_CYLINDER_HIGH, lba_high_byte);

    // set sector count
    outb(PRIMARY_ATA_SECTOR_COUNT, sector_count);

    // issue read command
    outb(PRIMARY_ATA_COMMAND_AND_STATUS, READ_SECTOR_COMMAND);

    for (int s = 0; s < sector_count; s++)
    {
        wait_for_ATA_device();
        for (int i = 0; i < 256; i++)
        {
            buffer[s * 256 + i] = inw(PRIMARY_ATA_DATA);
        }
    }
}

void init_ATA_HDD()
{
    select_master_ATA_device();
}