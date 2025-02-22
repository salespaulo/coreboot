ifeq ($(CONFIG_SOC_MEDIATEK_MT8195),y)

bootblock-y += bootblock.c
bootblock-y += ../common/eint_event.c
bootblock-y += ../common/flash_controller.c
bootblock-y += ../common/gpio.c gpio.c
bootblock-y += ../common/i2c.c i2c.c
bootblock-y += ../common/mmu_operations.c
bootblock-y += ../common/pll.c pll.c
bootblock-$(CONFIG_SPI_FLASH) += ../common/spi.c spi.c
bootblock-y += ../common/timer.c timer.c
bootblock-y += ../common/uart.c
bootblock-y += ../common/wdt.c

verstage-y += ../common/flash_controller.c
verstage-y += ../common/gpio.c gpio.c
verstage-y += ../common/i2c.c i2c.c
verstage-$(CONFIG_SPI_FLASH) += ../common/spi.c spi.c
verstage-y += ../common/timer.c timer.c
verstage-y += ../common/uart.c
verstage-y += ../common/wdt.c

romstage-y += ../common/cbmem.c
romstage-y += ../common/clkbuf.c
romstage-y += ../common/dram_init.c
romstage-y += ../common/dramc_param.c
romstage-y += emi.c
romstage-y += ../common/flash_controller.c
romstage-y += ../common/gpio.c gpio.c
romstage-y += ../common/i2c.c i2c.c
romstage-y += ../common/memory.c
romstage-y += ../common/memory_test.c
romstage-y += ../common/mmu_operations.c mmu_operations.c
romstage-y += ../common/pll.c pll.c
romstage-y += scp.c
romstage-$(CONFIG_SPI_FLASH) += ../common/spi.c spi.c
romstage-y += ../common/timer.c timer.c
romstage-y += ../common/uart.c
romstage-y += ../common/wdt.c
romstage-y += ../common/pmif.c ../common/pmif_clk.c pmif_clk.c
romstage-y += ../common/pmif_spi.c pmif_spi.c
romstage-y += ../common/pmif_spmi.c pmif_spmi.c
romstage-y += ../common/mt6315.c mt6315.c
romstage-y += ../common/mt6359p.c mt6359p.c
romstage-y += ../common/rtc.c ../common/rtc_osc_init.c ../common/rtc_mt6359p.c

ramstage-y += emi.c
ramstage-y += ../common/flash_controller.c
ramstage-y += ../common/gpio.c gpio.c
ramstage-y += ../common/i2c.c i2c.c
ramstage-y += ../common/mcu.c
ramstage-y += ../common/mcupm.c
ramstage-y += ../common/mmu_operations.c mmu_operations.c
ramstage-y += ../common/mtcmos.c mtcmos.c
ramstage-$(CONFIG_SPI_FLASH) += ../common/spi.c spi.c
ramstage-y += soc.c
ramstage-y += ../common/timer.c timer.c
ramstage-y += ../common/uart.c
ramstage-y += ../common/ufs.c
ramstage-y += ../common/usb.c usb.c
ramstage-y += ../common/wdt.c
ramstage-y += mt6360.c

BL31_MAKEARGS += PLAT=mt8195

MT8195_BLOB_DIR := 3rdparty/blobs/soc/mediatek/mt8195

mcu-firmware-files := \
	$(CONFIG_MCUPM_FIRMWARE)

$(foreach fw, $(call strip_quotes,$(mcu-firmware-files)), \
	  $(eval $(fw)-file := $(MT8195_BLOB_DIR)/$(fw)) \
	  $(eval $(fw)-type := raw) \
	  $(eval $(fw)-compression := LZ4) \
	  $(if $(wildcard $($(fw)-file)), $(eval cbfs-files-y += $(fw)), ) \
)

DRAM_CBFS := $(CONFIG_CBFS_PREFIX)/dram
$(DRAM_CBFS)-file := $(MT8195_BLOB_DIR)/dram.elf
$(DRAM_CBFS)-type := stage
$(DRAM_CBFS)-compression := $(CBFS_PRERAM_COMPRESS_FLAG)
ifneq ($(wildcard $($(DRAM_CBFS)-file)),)
	cbfs-files-y += $(DRAM_CBFS)
endif

CPPFLAGS_common += -Isrc/soc/mediatek/mt8195/include
CPPFLAGS_common += -Isrc/soc/mediatek/common/include
CPPFLAGS_common += -Isrc/vendorcode/mediatek/mt8195/include

$(objcbfs)/bootblock.bin: $(objcbfs)/bootblock.raw.bin
	./util/mtkheader/gen-bl-img.py mt8183 sf $< $@

endif
