/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2016-2017 Linaro Ltd., Rob Herring <robh@kernel.org>
 */
#ifndef _SERPORT_H
#define _SERPORT_H

struct serport {
	struct tty_port *port;
	struct tty_struct *tty;
	struct tty_driver *tty_drv;
	int tty_idx;
	unsigned long flags;
};

#endif
