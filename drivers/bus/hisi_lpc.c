<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2017 Hisilicon Limited, All Rights Reserved.
 * Author: Zhichang Yuan <yuanzhichang@hisilicon.com>
 * Author: Zou Rongrong <zourongrong@huawei.com>
 * Author: John Garry <john.garry@huawei.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/console.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/logic_pपन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pci.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/slab.h>

#घोषणा DRV_NAME "hisi-lpc"

/*
 * Setting this bit means each IO operation will target a dअगरferent port
 * address; 0 means repeated IO operations will use the same port,
 * such as BT.
 */
#घोषणा FG_INCRADDR_LPC		0x02

काष्ठा lpc_cycle_para अणु
	अचिन्हित पूर्णांक opflags;
	अचिन्हित पूर्णांक csize; /* data length of each operation */
पूर्ण;

काष्ठा hisi_lpc_dev अणु
	spinlock_t cycle_lock;
	व्योम __iomem  *membase;
	काष्ठा logic_pio_hwaddr *io_host;
पूर्ण;

/* The max IO cycle counts supported is four per operation at maximum */
#घोषणा LPC_MAX_DWIDTH	4

#घोषणा LPC_REG_STARTUP_SIGNAL		0x00
#घोषणा LPC_REG_STARTUP_SIGNAL_START	BIT(0)
#घोषणा LPC_REG_OP_STATUS		0x04
#घोषणा LPC_REG_OP_STATUS_IDLE		BIT(0)
#घोषणा LPC_REG_OP_STATUS_FINISHED	BIT(1)
#घोषणा LPC_REG_OP_LEN			0x10 /* LPC cycles count per start */
#घोषणा LPC_REG_CMD			0x14
#घोषणा LPC_REG_CMD_OP			BIT(0) /* 0: पढ़ो, 1: ग_लिखो */
#घोषणा LPC_REG_CMD_SAMEADDR		BIT(3)
#घोषणा LPC_REG_ADDR			0x20 /* target address */
#घोषणा LPC_REG_WDATA			0x24 /* ग_लिखो FIFO */
#घोषणा LPC_REG_RDATA			0x28 /* पढ़ो FIFO */

/* The minimal nanosecond पूर्णांकerval क्रम each query on LPC cycle status */
#घोषणा LPC_NSEC_PERWAIT	100

/*
 * The maximum रुकोing समय is about 128us.  It is specअगरic क्रम stream I/O,
 * such as ins.
 *
 * The fastest IO cycle समय is about 390ns, but the worst हाल will रुको
 * क्रम extra 256 lpc घड़ीs, so (256 + 13) * 30ns = 8 us. The maximum burst
 * cycles is 16. So, the maximum रुकोing समय is about 128us under worst
 * हाल.
 *
 * Choose 1300 as the maximum.
 */
#घोषणा LPC_MAX_WAITCNT		1300

/* About 10us. This is specअगरic क्रम single IO operations, such as inb */
#घोषणा LPC_PEROP_WAITCNT	100

अटल पूर्णांक रुको_lpc_idle(व्योम __iomem *mbase, अचिन्हित पूर्णांक रुकोcnt)
अणु
	u32 status;

	करो अणु
		status = पढ़ोl(mbase + LPC_REG_OP_STATUS);
		अगर (status & LPC_REG_OP_STATUS_IDLE)
			वापस (status & LPC_REG_OP_STATUS_FINISHED) ? 0 : -EIO;
		ndelay(LPC_NSEC_PERWAIT);
	पूर्ण जबतक (--रुकोcnt);

	वापस -ETIME;
पूर्ण

/*
 * hisi_lpc_target_in - trigger a series of LPC cycles क्रम पढ़ो operation
 * @lpcdev: poपूर्णांकer to hisi lpc device
 * @para: some parameters used to control the lpc I/O operations
 * @addr: the lpc I/O target port address
 * @buf: where the पढ़ो back data is stored
 * @opcnt: how many I/O operations required, i.e. data width
 *
 * Returns 0 on success, non-zero on fail.
 */
अटल पूर्णांक hisi_lpc_target_in(काष्ठा hisi_lpc_dev *lpcdev,
			      काष्ठा lpc_cycle_para *para, अचिन्हित दीर्घ addr,
			      अचिन्हित अक्षर *buf, अचिन्हित दीर्घ opcnt)
अणु
	अचिन्हित पूर्णांक cmd_word;
	अचिन्हित पूर्णांक रुकोcnt;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!buf || !opcnt || !para || !para->csize || !lpcdev)
		वापस -EINVAL;

	cmd_word = 0; /* IO mode, Read */
	रुकोcnt = LPC_PEROP_WAITCNT;
	अगर (!(para->opflags & FG_INCRADDR_LPC)) अणु
		cmd_word |= LPC_REG_CMD_SAMEADDR;
		रुकोcnt = LPC_MAX_WAITCNT;
	पूर्ण

	/* whole operation must be atomic */
	spin_lock_irqsave(&lpcdev->cycle_lock, flags);

	ग_लिखोl_relaxed(opcnt, lpcdev->membase + LPC_REG_OP_LEN);
	ग_लिखोl_relaxed(cmd_word, lpcdev->membase + LPC_REG_CMD);
	ग_लिखोl_relaxed(addr, lpcdev->membase + LPC_REG_ADDR);

	ग_लिखोl(LPC_REG_STARTUP_SIGNAL_START,
	       lpcdev->membase + LPC_REG_STARTUP_SIGNAL);

	/* whether the operation is finished */
	ret = रुको_lpc_idle(lpcdev->membase, रुकोcnt);
	अगर (ret) अणु
		spin_unlock_irqrestore(&lpcdev->cycle_lock, flags);
		वापस ret;
	पूर्ण

	पढ़ोsb(lpcdev->membase + LPC_REG_RDATA, buf, opcnt);

	spin_unlock_irqrestore(&lpcdev->cycle_lock, flags);

	वापस 0;
पूर्ण

/*
 * hisi_lpc_target_out - trigger a series of LPC cycles क्रम ग_लिखो operation
 * @lpcdev: poपूर्णांकer to hisi lpc device
 * @para: some parameters used to control the lpc I/O operations
 * @addr: the lpc I/O target port address
 * @buf: where the data to be written is stored
 * @opcnt: how many I/O operations required, i.e. data width
 *
 * Returns 0 on success, non-zero on fail.
 */
अटल पूर्णांक hisi_lpc_target_out(काष्ठा hisi_lpc_dev *lpcdev,
			       काष्ठा lpc_cycle_para *para, अचिन्हित दीर्घ addr,
			       स्थिर अचिन्हित अक्षर *buf, अचिन्हित दीर्घ opcnt)
अणु
	अचिन्हित पूर्णांक रुकोcnt;
	अचिन्हित दीर्घ flags;
	u32 cmd_word;
	पूर्णांक ret;

	अगर (!buf || !opcnt || !para || !lpcdev)
		वापस -EINVAL;

	/* शेष is increasing address */
	cmd_word = LPC_REG_CMD_OP; /* IO mode, ग_लिखो */
	रुकोcnt = LPC_PEROP_WAITCNT;
	अगर (!(para->opflags & FG_INCRADDR_LPC)) अणु
		cmd_word |= LPC_REG_CMD_SAMEADDR;
		रुकोcnt = LPC_MAX_WAITCNT;
	पूर्ण

	spin_lock_irqsave(&lpcdev->cycle_lock, flags);

	ग_लिखोl_relaxed(opcnt, lpcdev->membase + LPC_REG_OP_LEN);
	ग_लिखोl_relaxed(cmd_word, lpcdev->membase + LPC_REG_CMD);
	ग_लिखोl_relaxed(addr, lpcdev->membase + LPC_REG_ADDR);

	ग_लिखोsb(lpcdev->membase + LPC_REG_WDATA, buf, opcnt);

	ग_लिखोl(LPC_REG_STARTUP_SIGNAL_START,
	       lpcdev->membase + LPC_REG_STARTUP_SIGNAL);

	/* whether the operation is finished */
	ret = रुको_lpc_idle(lpcdev->membase, रुकोcnt);

	spin_unlock_irqrestore(&lpcdev->cycle_lock, flags);

	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ hisi_lpc_pio_to_addr(काष्ठा hisi_lpc_dev *lpcdev,
					  अचिन्हित दीर्घ pio)
अणु
	वापस pio - lpcdev->io_host->io_start + lpcdev->io_host->hw_start;
पूर्ण

/*
 * hisi_lpc_comm_in - input the data in a single operation
 * @hostdata: poपूर्णांकer to the device inक्रमmation relevant to LPC controller
 * @pio: the target I/O port address
 * @dwidth: the data length required to पढ़ो from the target I/O port
 *
 * When success, data is वापसed. Otherwise, ~0 is वापसed.
 */
अटल u32 hisi_lpc_comm_in(व्योम *hostdata, अचिन्हित दीर्घ pio, माप_प्रकार dwidth)
अणु
	काष्ठा hisi_lpc_dev *lpcdev = hostdata;
	काष्ठा lpc_cycle_para iopara;
	अचिन्हित दीर्घ addr;
	__le32 rd_data = 0;
	पूर्णांक ret;

	अगर (!lpcdev || !dwidth || dwidth > LPC_MAX_DWIDTH)
		वापस ~0;

	addr = hisi_lpc_pio_to_addr(lpcdev, pio);

	iopara.opflags = FG_INCRADDR_LPC;
	iopara.csize = dwidth;

	ret = hisi_lpc_target_in(lpcdev, &iopara, addr,
				 (अचिन्हित अक्षर *)&rd_data, dwidth);
	अगर (ret)
		वापस ~0;

	वापस le32_to_cpu(rd_data);
पूर्ण

/*
 * hisi_lpc_comm_out - output the data in a single operation
 * @hostdata: poपूर्णांकer to the device inक्रमmation relevant to LPC controller
 * @pio: the target I/O port address
 * @val: a value to be output from caller, maximum is four bytes
 * @dwidth: the data width required writing to the target I/O port
 *
 * This function corresponds to out(b,w,l) only.
 */
अटल व्योम hisi_lpc_comm_out(व्योम *hostdata, अचिन्हित दीर्घ pio,
			      u32 val, माप_प्रकार dwidth)
अणु
	काष्ठा hisi_lpc_dev *lpcdev = hostdata;
	काष्ठा lpc_cycle_para iopara;
	स्थिर अचिन्हित अक्षर *buf;
	अचिन्हित दीर्घ addr;
	__le32 _val = cpu_to_le32(val);

	अगर (!lpcdev || !dwidth || dwidth > LPC_MAX_DWIDTH)
		वापस;

	buf = (स्थिर अचिन्हित अक्षर *)&_val;
	addr = hisi_lpc_pio_to_addr(lpcdev, pio);

	iopara.opflags = FG_INCRADDR_LPC;
	iopara.csize = dwidth;

	hisi_lpc_target_out(lpcdev, &iopara, addr, buf, dwidth);
पूर्ण

/*
 * hisi_lpc_comm_ins - input the data in the buffer in multiple operations
 * @hostdata: poपूर्णांकer to the device inक्रमmation relevant to LPC controller
 * @pio: the target I/O port address
 * @buffer: a buffer where पढ़ो/input data bytes are stored
 * @dwidth: the data width required writing to the target I/O port
 * @count: how many data units whose length is dwidth will be पढ़ो
 *
 * When success, the data पढ़ो back is stored in buffer poपूर्णांकed by buffer.
 * Returns 0 on success, -त्रुटि_सं otherwise.
 */
अटल u32 hisi_lpc_comm_ins(व्योम *hostdata, अचिन्हित दीर्घ pio, व्योम *buffer,
			     माप_प्रकार dwidth, अचिन्हित पूर्णांक count)
अणु
	काष्ठा hisi_lpc_dev *lpcdev = hostdata;
	अचिन्हित अक्षर *buf = buffer;
	काष्ठा lpc_cycle_para iopara;
	अचिन्हित दीर्घ addr;

	अगर (!lpcdev || !buf || !count || !dwidth || dwidth > LPC_MAX_DWIDTH)
		वापस -EINVAL;

	iopara.opflags = 0;
	अगर (dwidth > 1)
		iopara.opflags |= FG_INCRADDR_LPC;
	iopara.csize = dwidth;

	addr = hisi_lpc_pio_to_addr(lpcdev, pio);

	करो अणु
		पूर्णांक ret;

		ret = hisi_lpc_target_in(lpcdev, &iopara, addr, buf, dwidth);
		अगर (ret)
			वापस ret;
		buf += dwidth;
	पूर्ण जबतक (--count);

	वापस 0;
पूर्ण

/*
 * hisi_lpc_comm_outs - output the data in the buffer in multiple operations
 * @hostdata: poपूर्णांकer to the device inक्रमmation relevant to LPC controller
 * @pio: the target I/O port address
 * @buffer: a buffer where ग_लिखो/output data bytes are stored
 * @dwidth: the data width required writing to the target I/O port
 * @count: how many data units whose length is dwidth will be written
 */
अटल व्योम hisi_lpc_comm_outs(व्योम *hostdata, अचिन्हित दीर्घ pio,
			       स्थिर व्योम *buffer, माप_प्रकार dwidth,
			       अचिन्हित पूर्णांक count)
अणु
	काष्ठा hisi_lpc_dev *lpcdev = hostdata;
	काष्ठा lpc_cycle_para iopara;
	स्थिर अचिन्हित अक्षर *buf = buffer;
	अचिन्हित दीर्घ addr;

	अगर (!lpcdev || !buf || !count || !dwidth || dwidth > LPC_MAX_DWIDTH)
		वापस;

	iopara.opflags = 0;
	अगर (dwidth > 1)
		iopara.opflags |= FG_INCRADDR_LPC;
	iopara.csize = dwidth;

	addr = hisi_lpc_pio_to_addr(lpcdev, pio);
	करो अणु
		अगर (hisi_lpc_target_out(lpcdev, &iopara, addr, buf, dwidth))
			अवरोध;
		buf += dwidth;
	पूर्ण जबतक (--count);
पूर्ण

अटल स्थिर काष्ठा logic_pio_host_ops hisi_lpc_ops = अणु
	.in = hisi_lpc_comm_in,
	.out = hisi_lpc_comm_out,
	.ins = hisi_lpc_comm_ins,
	.outs = hisi_lpc_comm_outs,
पूर्ण;

#अगर_घोषित CONFIG_ACPI
अटल पूर्णांक hisi_lpc_acpi_xlat_io_res(काष्ठा acpi_device *adev,
				     काष्ठा acpi_device *host,
				     काष्ठा resource *res)
अणु
	अचिन्हित दीर्घ sys_port;
	resource_माप_प्रकार len = resource_size(res);

	sys_port = logic_pio_trans_hwaddr(&host->fwnode, res->start, len);
	अगर (sys_port == ~0UL)
		वापस -EFAULT;

	res->start = sys_port;
	res->end = sys_port + len;

	वापस 0;
पूर्ण

/*
 * Released firmware describes the IO port max address as 0x3fff, which is
 * the max host bus address. Fixup to a proper range. This will probably
 * never be fixed in firmware.
 */
अटल व्योम hisi_lpc_acpi_fixup_child_resource(काष्ठा device *hostdev,
					       काष्ठा resource *r)
अणु
	अगर (r->end != 0x3fff)
		वापस;

	अगर (r->start == 0xe4)
		r->end = 0xe4 + 0x04 - 1;
	अन्यथा अगर (r->start == 0x2f8)
		r->end = 0x2f8 + 0x08 - 1;
	अन्यथा
		dev_warn(hostdev, "unrecognised resource %pR to fixup, ignoring\n",
			 r);
पूर्ण

/*
 * hisi_lpc_acpi_set_io_res - set the resources क्रम a child
 * @child: the device node to be updated the I/O resource
 * @hostdev: the device node associated with host controller
 * @res: द्विगुन poपूर्णांकer to be set to the address of translated resources
 * @num_res: poपूर्णांकer to variable to hold the number of translated resources
 *
 * Returns 0 when successful, and a negative value क्रम failure.
 *
 * For a given host controller, each child device will have an associated
 * host-relative address resource.  This function will वापस the translated
 * logical PIO addresses क्रम each child devices resources.
 */
अटल पूर्णांक hisi_lpc_acpi_set_io_res(काष्ठा device *child,
				    काष्ठा device *hostdev,
				    स्थिर काष्ठा resource **res, पूर्णांक *num_res)
अणु
	काष्ठा acpi_device *adev;
	काष्ठा acpi_device *host;
	काष्ठा resource_entry *rentry;
	LIST_HEAD(resource_list);
	काष्ठा resource *resources;
	पूर्णांक count;
	पूर्णांक i;

	अगर (!child || !hostdev)
		वापस -EINVAL;

	host = to_acpi_device(hostdev);
	adev = to_acpi_device(child);

	अगर (!adev->status.present) अणु
		dev_dbg(child, "device is not present\n");
		वापस -EIO;
	पूर्ण

	अगर (acpi_device_क्रमागतerated(adev)) अणु
		dev_dbg(child, "has been enumerated\n");
		वापस -EIO;
	पूर्ण

	/*
	 * The following code segment to retrieve the resources is common to
	 * acpi_create_platक्रमm_device(), so consider a common helper function
	 * in future.
	 */
	count = acpi_dev_get_resources(adev, &resource_list, शून्य, शून्य);
	अगर (count <= 0) अणु
		dev_dbg(child, "failed to get resources\n");
		वापस count ? count : -EIO;
	पूर्ण

	resources = devm_kसुस्मृति(hostdev, count, माप(*resources),
				 GFP_KERNEL);
	अगर (!resources) अणु
		dev_warn(hostdev, "could not allocate memory for %d resources\n",
			 count);
		acpi_dev_मुक्त_resource_list(&resource_list);
		वापस -ENOMEM;
	पूर्ण
	count = 0;
	list_क्रम_each_entry(rentry, &resource_list, node) अणु
		resources[count] = *rentry->res;
		hisi_lpc_acpi_fixup_child_resource(hostdev, &resources[count]);
		count++;
	पूर्ण

	acpi_dev_मुक्त_resource_list(&resource_list);

	/* translate the I/O resources */
	क्रम (i = 0; i < count; i++) अणु
		पूर्णांक ret;

		अगर (!(resources[i].flags & IORESOURCE_IO))
			जारी;
		ret = hisi_lpc_acpi_xlat_io_res(adev, host, &resources[i]);
		अगर (ret) अणु
			dev_err(child, "translate IO range %pR failed (%d)\n",
				&resources[i], ret);
			वापस ret;
		पूर्ण
	पूर्ण
	*res = resources;
	*num_res = count;

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_lpc_acpi_हटाओ_subdev(काष्ठा device *dev, व्योम *unused)
अणु
	platक्रमm_device_unरेजिस्टर(to_platक्रमm_device(dev));
	वापस 0;
पूर्ण

काष्ठा hisi_lpc_acpi_cell अणु
	स्थिर अक्षर *hid;
	स्थिर अक्षर *name;
	व्योम *pdata;
	माप_प्रकार pdata_size;
पूर्ण;

अटल व्योम hisi_lpc_acpi_हटाओ(काष्ठा device *hostdev)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(hostdev);
	काष्ठा acpi_device *child;

	device_क्रम_each_child(hostdev, शून्य, hisi_lpc_acpi_हटाओ_subdev);

	list_क्रम_each_entry(child, &adev->children, node)
		acpi_device_clear_क्रमागतerated(child);
पूर्ण

/*
 * hisi_lpc_acpi_probe - probe children क्रम ACPI FW
 * @hostdev: LPC host device poपूर्णांकer
 *
 * Returns 0 when successful, and a negative value क्रम failure.
 *
 * Create a platक्रमm device per child, fixing up the resources
 * from bus addresses to Logical PIO addresses.
 *
 */
अटल पूर्णांक hisi_lpc_acpi_probe(काष्ठा device *hostdev)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(hostdev);
	काष्ठा acpi_device *child;
	पूर्णांक ret;

	/* Only consider the children of the host */
	list_क्रम_each_entry(child, &adev->children, node) अणु
		स्थिर अक्षर *hid = acpi_device_hid(child);
		स्थिर काष्ठा hisi_lpc_acpi_cell *cell;
		काष्ठा platक्रमm_device *pdev;
		स्थिर काष्ठा resource *res;
		bool found = false;
		पूर्णांक num_res;

		ret = hisi_lpc_acpi_set_io_res(&child->dev, &adev->dev, &res,
					       &num_res);
		अगर (ret) अणु
			dev_warn(hostdev, "set resource fail (%d)\n", ret);
			जाओ fail;
		पूर्ण

		cell = (काष्ठा hisi_lpc_acpi_cell [])अणु
			/* ipmi */
			अणु
				.hid = "IPI0001",
				.name = "hisi-lpc-ipmi",
			पूर्ण,
			/* 8250-compatible uart */
			अणु
				.hid = "HISI1031",
				.name = "serial8250",
				.pdata = (काष्ठा plat_serial8250_port []) अणु
					अणु
						.iobase = res->start,
						.uartclk = 1843200,
						.iotype = UPIO_PORT,
						.flags = UPF_BOOT_AUTOCONF,
					पूर्ण,
					अणुपूर्ण
				पूर्ण,
				.pdata_size = 2 *
					माप(काष्ठा plat_serial8250_port),
			पूर्ण,
			अणुपूर्ण
		पूर्ण;

		क्रम (; cell && cell->name; cell++) अणु
			अगर (!म_भेद(cell->hid, hid)) अणु
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!found) अणु
			dev_warn(hostdev,
				 "could not find cell for child device (%s), discarding\n",
				 hid);
			जारी;
		पूर्ण

		pdev = platक्रमm_device_alloc(cell->name, PLATFORM_DEVID_AUTO);
		अगर (!pdev) अणु
			ret = -ENOMEM;
			जाओ fail;
		पूर्ण

		pdev->dev.parent = hostdev;
		ACPI_COMPANION_SET(&pdev->dev, child);

		ret = platक्रमm_device_add_resources(pdev, res, num_res);
		अगर (ret)
			जाओ fail;

		ret = platक्रमm_device_add_data(pdev, cell->pdata,
					       cell->pdata_size);
		अगर (ret)
			जाओ fail;

		ret = platक्रमm_device_add(pdev);
		अगर (ret)
			जाओ fail;

		acpi_device_set_क्रमागतerated(child);
	पूर्ण

	वापस 0;

fail:
	hisi_lpc_acpi_हटाओ(hostdev);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id hisi_lpc_acpi_match[] = अणु
	अणु"HISI0191"पूर्ण,
	अणुपूर्ण
पूर्ण;
#अन्यथा
अटल पूर्णांक hisi_lpc_acpi_probe(काष्ठा device *dev)
अणु
	वापस -ENODEV;
पूर्ण

अटल व्योम hisi_lpc_acpi_हटाओ(काष्ठा device *hostdev)
अणु
पूर्ण
#पूर्ण_अगर // CONFIG_ACPI

/*
 * hisi_lpc_probe - the probe callback function क्रम hisi lpc host,
 *		   will finish all the initialization.
 * @pdev: the platक्रमm device corresponding to hisi lpc host
 *
 * Returns 0 on success, non-zero on fail.
 */
अटल पूर्णांक hisi_lpc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा acpi_device *acpi_device = ACPI_COMPANION(dev);
	काष्ठा logic_pio_hwaddr *range;
	काष्ठा hisi_lpc_dev *lpcdev;
	resource_माप_प्रकार io_end;
	काष्ठा resource *res;
	पूर्णांक ret;

	lpcdev = devm_kzalloc(dev, माप(*lpcdev), GFP_KERNEL);
	अगर (!lpcdev)
		वापस -ENOMEM;

	spin_lock_init(&lpcdev->cycle_lock);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	lpcdev->membase = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(lpcdev->membase))
		वापस PTR_ERR(lpcdev->membase);

	range = devm_kzalloc(dev, माप(*range), GFP_KERNEL);
	अगर (!range)
		वापस -ENOMEM;

	range->fwnode = dev->fwnode;
	range->flags = LOGIC_PIO_INसूचीECT;
	range->size = PIO_INसूचीECT_SIZE;
	range->hostdata = lpcdev;
	range->ops = &hisi_lpc_ops;
	lpcdev->io_host = range;

	ret = logic_pio_रेजिस्टर_range(range);
	अगर (ret) अणु
		dev_err(dev, "register IO range failed (%d)!\n", ret);
		वापस ret;
	पूर्ण

	/* रेजिस्टर the LPC host PIO resources */
	अगर (acpi_device)
		ret = hisi_lpc_acpi_probe(dev);
	अन्यथा
		ret = of_platक्रमm_populate(dev->of_node, शून्य, शून्य, dev);
	अगर (ret) अणु
		logic_pio_unरेजिस्टर_range(range);
		वापस ret;
	पूर्ण

	dev_set_drvdata(dev, lpcdev);

	io_end = lpcdev->io_host->io_start + lpcdev->io_host->size;
	dev_info(dev, "registered range [%pa - %pa]\n",
		 &lpcdev->io_host->io_start, &io_end);

	वापस ret;
पूर्ण

अटल पूर्णांक hisi_lpc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा acpi_device *acpi_device = ACPI_COMPANION(dev);
	काष्ठा hisi_lpc_dev *lpcdev = dev_get_drvdata(dev);
	काष्ठा logic_pio_hwaddr *range = lpcdev->io_host;

	अगर (acpi_device)
		hisi_lpc_acpi_हटाओ(dev);
	अन्यथा
		of_platक्रमm_depopulate(dev);

	logic_pio_unरेजिस्टर_range(range);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id hisi_lpc_of_match[] = अणु
	अणु .compatible = "hisilicon,hip06-lpc", पूर्ण,
	अणु .compatible = "hisilicon,hip07-lpc", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver hisi_lpc_driver = अणु
	.driver = अणु
		.name           = DRV_NAME,
		.of_match_table = hisi_lpc_of_match,
		.acpi_match_table = ACPI_PTR(hisi_lpc_acpi_match),
	पूर्ण,
	.probe = hisi_lpc_probe,
	.हटाओ = hisi_lpc_हटाओ,
पूर्ण;
builtin_platक्रमm_driver(hisi_lpc_driver);
