/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <baseboard/gpio.h>
#include <baseboard/variants.h>

/* Pad configuration in ramstage*/
static const struct pad_config gpio_table[] = {
	/* A10 : WWAN_EN */
	PAD_CFG_GPO(GPP_A10, 1, PWROK),

	/* B7  : PCIE_CLKREQ2_N ==> WWAN_SAR_DETECT_ODL*/
	PAD_CFG_GPI_IRQ_WAKE(GPP_B7, NONE, DEEP, LEVEL, INVERT),

	/* C12 : AP_PEN_DET_ODL */
	PAD_CFG_GPI_GPIO_DRIVER(GPP_C12, UP_20K, DEEP),

	/* D15 : EN_PP3300_CAMERA */
	PAD_CFG_GPO(GPP_D15, 1, PLTRST),
	/* D22 : AP_I2C_SUB_SDA*/
	PAD_CFG_NF(GPP_D22, NONE, DEEP, NF1),
	/* D23 : AP_I2C_SUB_SCL */
	PAD_CFG_NF(GPP_D23, NONE, DEEP, NF1),

	/* E11 : AP_I2C_SUB_INT_ODL */
	PAD_CFG_GPI_APIC(GPP_E11, NONE, PLTRST, LEVEL, NONE),

	/* H17 : WWAN_RST_L */
	PAD_CFG_GPO(GPP_H17, 0, PLTRST),
};

const struct pad_config *variant_override_gpio_table(size_t *num)
{
	*num = ARRAY_SIZE(gpio_table);
	return gpio_table;
}
