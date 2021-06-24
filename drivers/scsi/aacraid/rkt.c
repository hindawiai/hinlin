<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	Adaptec AAC series RAID controller driver
 *	(c) Copyright 2001 Red Hat Inc.
 *
 * based on the old aacraid driver that is..
 * Adaptec aacraid device driver क्रम Linux.
 *
 * Copyright (c) 2000-2010 Adaptec, Inc.
 *               2010-2015 PMC-Sierra, Inc. (aacraid@pmc-sierra.com)
 *		 2016-2017 Microsemi Corp. (aacraid@microsemi.com)
 *
 * Module Name:
 *  rkt.c
 *
 * Abstract: Hardware miniport क्रम Drawbridge specअगरic hardware functions.
 */

#समावेश <linux/blkdev.h>

#समावेश <scsi/scsi_host.h>

#समावेश "aacraid.h"

#घोषणा AAC_NUM_IO_FIB_RKT      (246 - AAC_NUM_MGT_FIB)

/**
 *	aac_rkt_select_comm	-	Select communications method
 *	@dev: Adapter
 *	@comm: communications method
 */

अटल पूर्णांक aac_rkt_select_comm(काष्ठा aac_dev *dev, पूर्णांक comm)
अणु
	पूर्णांक retval;
	retval = aac_rx_select_comm(dev, comm);
	अगर (comm == AAC_COMM_MESSAGE) अणु
		/*
		 * FIB Setup has alपढ़ोy been करोne, but we can minimize the
		 * damage by at least ensuring the OS never issues more
		 * commands than we can handle. The Rocket adapters currently
		 * can only handle 246 commands and 8 AIFs at the same समय,
		 * and in fact करो notअगरy us accordingly अगर we negotiate the
		 * FIB size. The problem that causes us to add this check is
		 * to ensure that we करो not overकरो it with the adapter when a
		 * hard coded FIB override is being utilized. This special
		 * हाल warrants this half baked, but convenient, check here.
		 */
		अगर (dev->scsi_host_ptr->can_queue > AAC_NUM_IO_FIB_RKT) अणु
			dev->init->r7.max_io_commands =
				cpu_to_le32(AAC_NUM_IO_FIB_RKT + AAC_NUM_MGT_FIB);
			dev->scsi_host_ptr->can_queue = AAC_NUM_IO_FIB_RKT;
		पूर्ण
	पूर्ण
	वापस retval;
पूर्ण

/**
 *	aac_rkt_ioremap
 *	@dev: device to ioremap
 *	@size: mapping resize request
 *
 */
अटल पूर्णांक aac_rkt_ioremap(काष्ठा aac_dev * dev, u32 size)
अणु
	अगर (!size) अणु
		iounmap(dev->regs.rkt);
		वापस 0;
	पूर्ण
	dev->base = dev->regs.rkt = ioremap(dev->base_start, size);
	अगर (dev->base == शून्य)
		वापस -1;
	dev->IndexRegs = &dev->regs.rkt->IndexRegs;
	वापस 0;
पूर्ण

/**
 *	aac_rkt_init	-	initialize an i960 based AAC card
 *	@dev: device to configure
 *
 *	Allocate and set up resources क्रम the i960 based AAC variants. The
 *	device_पूर्णांकerface in the commregion will be allocated and linked
 *	to the comm region.
 */

पूर्णांक aac_rkt_init(काष्ठा aac_dev *dev)
अणु
	/*
	 *	Fill in the function dispatch table.
	 */
	dev->a_ops.adapter_ioremap = aac_rkt_ioremap;
	dev->a_ops.adapter_comm = aac_rkt_select_comm;

	वापस _aac_rx_init(dev);
पूर्ण
