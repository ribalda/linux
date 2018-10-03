// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright 2018 Qtechnology A/S
 *
 * Ricardo Ribalda <ricardo.ribalda@gmail.com>
 *
 */
#include <linux/platform_device.h>
#include "gpio-addr-flash.h"

int of_flash_probe_gpio(struct platform_device *pdev, struct device_node *np,
			struct map_info *map)
{
	struct async_state *state;

	state = devm_kzalloc(&pdev->dev, sizeof(*state), GFP_KERNEL);
	if (!state)
		return -ENOMEM;

	return gpio_flash_probe_common(&pdev->dev, state, map);
}
