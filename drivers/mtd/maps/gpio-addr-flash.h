/* SPDX-License-Identifier: GPL-2.0 */
#include <linux/of.h>
#include <linux/mtd/map.h>

/**
 * struct async_state - keep GPIO flash state
 *	@gpios:       Struct containing the array of GPIO descriptors
 *	@gpio_values: cached GPIO values
 *	@win_order:   dedicated memory size (if no GPIOs)
 */
struct async_state {
	struct gpio_descs *gpios;
	unsigned int gpio_values;
	unsigned int win_order;
};

int gpio_flash_probe_common(struct device *dev,
				   struct async_state *state,
				   struct map_info *map);

#ifdef CONFIG_MTD_PHYSMAP_OF_GPIO
int of_flash_probe_gpio(struct platform_device *pdev, struct device_node *np,
			struct map_info *map);
#else
static inline
int of_flash_probe_gpio(struct platform_device *pdev, struct device_node *np,
			struct map_info *map)
{
	return 0;
}
#endif
