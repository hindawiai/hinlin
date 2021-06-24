<शैली गुरु>
/*
 * CPU frequency scaling क्रम Broadcom SoCs with AVS firmware that
 * supports DVS or DVFS
 *
 * Copyright (c) 2016 Broadcom
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

/*
 * "AVS" is the name of a firmware developed at Broadcom. It derives
 * its name from the technique called "Adaptive Voltage Scaling".
 * Adaptive voltage scaling was the original purpose of this firmware.
 * The AVS firmware still supports "AVS mode", where all it करोes is
 * adaptive voltage scaling. However, on some newer Broadcom SoCs, the
 * AVS Firmware, despite its unchanged name, also supports DFS mode and
 * DVFS mode.
 *
 * In the context of this करोcument and the related driver, "AVS" by
 * itself always means the Broadcom firmware and never refers to the
 * technique called "Adaptive Voltage Scaling".
 *
 * The Broadcom STB AVS CPUfreq driver provides voltage and frequency
 * scaling on Broadcom SoCs using AVS firmware with support क्रम DFS and
 * DVFS. The AVS firmware is running on its own co-processor. The
 * driver supports both uniprocessor (UP) and symmetric multiprocessor
 * (SMP) प्रणालीs which share घड़ी and voltage across all CPUs.
 *
 * Actual voltage and frequency scaling is करोne solely by the AVS
 * firmware. This driver करोes not change frequency or voltage itself.
 * It provides a standard CPUfreq पूर्णांकerface to the rest of the kernel
 * and to userland. It पूर्णांकerfaces with the AVS firmware to effect the
 * requested changes and to report back the current प्रणाली status in a
 * way that is expected by existing tools.
 */

#समावेश <linux/cpufreq.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/semaphore.h>

/* Max number of arguments AVS calls take */
#घोषणा AVS_MAX_CMD_ARGS	4
/*
 * This macro is used to generate AVS parameter रेजिस्टर offsets. For
 * x >= AVS_MAX_CMD_ARGS, it वापसs 0 to protect against accidental memory
 * access outside of the parameter range. (Offset 0 is the first parameter.)
 */
#घोषणा AVS_PARAM_MULT(x)	((x) < AVS_MAX_CMD_ARGS ? (x) : 0)

/* AVS Mailbox Register offsets */
#घोषणा AVS_MBOX_COMMAND	0x00
#घोषणा AVS_MBOX_STATUS		0x04
#घोषणा AVS_MBOX_VOLTAGE0	0x08
#घोषणा AVS_MBOX_TEMP0		0x0c
#घोषणा AVS_MBOX_PV0		0x10
#घोषणा AVS_MBOX_MV0		0x14
#घोषणा AVS_MBOX_PARAM(x)	(0x18 + AVS_PARAM_MULT(x) * माप(u32))
#घोषणा AVS_MBOX_REVISION	0x28
#घोषणा AVS_MBOX_PSTATE		0x2c
#घोषणा AVS_MBOX_HEARTBEAT	0x30
#घोषणा AVS_MBOX_MAGIC		0x34
#घोषणा AVS_MBOX_SIGMA_HVT	0x38
#घोषणा AVS_MBOX_SIGMA_SVT	0x3c
#घोषणा AVS_MBOX_VOLTAGE1	0x40
#घोषणा AVS_MBOX_TEMP1		0x44
#घोषणा AVS_MBOX_PV1		0x48
#घोषणा AVS_MBOX_MV1		0x4c
#घोषणा AVS_MBOX_FREQUENCY	0x50

/* AVS Commands */
#घोषणा AVS_CMD_AVAILABLE	0x00
#घोषणा AVS_CMD_DISABLE		0x10
#घोषणा AVS_CMD_ENABLE		0x11
#घोषणा AVS_CMD_S2_ENTER	0x12
#घोषणा AVS_CMD_S2_EXIT		0x13
#घोषणा AVS_CMD_BBM_ENTER	0x14
#घोषणा AVS_CMD_BBM_EXIT	0x15
#घोषणा AVS_CMD_S3_ENTER	0x16
#घोषणा AVS_CMD_S3_EXIT		0x17
#घोषणा AVS_CMD_BALANCE		0x18
/* PMAP and P-STATE commands */
#घोषणा AVS_CMD_GET_PMAP	0x30
#घोषणा AVS_CMD_SET_PMAP	0x31
#घोषणा AVS_CMD_GET_PSTATE	0x40
#घोषणा AVS_CMD_SET_PSTATE	0x41

/* Dअगरferent modes AVS supports (क्रम GET_PMAP/SET_PMAP) */
#घोषणा AVS_MODE_AVS		0x0
#घोषणा AVS_MODE_DFS		0x1
#घोषणा AVS_MODE_DVS		0x2
#घोषणा AVS_MODE_DVFS		0x3

/*
 * PMAP parameter p1
 * unused:31-24, mभाग_p0:23-16, unused:15-14, pभाग:13-10 , nभाग_पूर्णांक:9-0
 */
#घोषणा NDIV_INT_SHIFT		0
#घोषणा NDIV_INT_MASK		0x3ff
#घोषणा PDIV_SHIFT		10
#घोषणा PDIV_MASK		0xf
#घोषणा MDIV_P0_SHIFT		16
#घोषणा MDIV_P0_MASK		0xff
/*
 * PMAP parameter p2
 * mभाग_p4:31-24, mभाग_p3:23-16, mभाग_p2:15:8, mभाग_p1:7:0
 */
#घोषणा MDIV_P1_SHIFT		0
#घोषणा MDIV_P1_MASK		0xff
#घोषणा MDIV_P2_SHIFT		8
#घोषणा MDIV_P2_MASK		0xff
#घोषणा MDIV_P3_SHIFT		16
#घोषणा MDIV_P3_MASK		0xff
#घोषणा MDIV_P4_SHIFT		24
#घोषणा MDIV_P4_MASK		0xff

/* Dअगरferent P-STATES AVS supports (क्रम GET_PSTATE/SET_PSTATE) */
#घोषणा AVS_PSTATE_P0		0x0
#घोषणा AVS_PSTATE_P1		0x1
#घोषणा AVS_PSTATE_P2		0x2
#घोषणा AVS_PSTATE_P3		0x3
#घोषणा AVS_PSTATE_P4		0x4
#घोषणा AVS_PSTATE_MAX		AVS_PSTATE_P4

/* CPU L2 Interrupt Controller Registers */
#घोषणा AVS_CPU_L2_SET0		0x04
#घोषणा AVS_CPU_L2_INT_MASK	BIT(31)

/* AVS Command Status Values */
#घोषणा AVS_STATUS_CLEAR	0x00
/* Command/notअगरication accepted */
#घोषणा AVS_STATUS_SUCCESS	0xf0
/* Command/notअगरication rejected */
#घोषणा AVS_STATUS_FAILURE	0xff
/* Invalid command/notअगरication (unknown) */
#घोषणा AVS_STATUS_INVALID	0xf1
/* Non-AVS modes are not supported */
#घोषणा AVS_STATUS_NO_SUPP	0xf2
/* Cannot set P-State until P-Map supplied */
#घोषणा AVS_STATUS_NO_MAP	0xf3
/* Cannot change P-Map after initial P-Map set */
#घोषणा AVS_STATUS_MAP_SET	0xf4
/* Max AVS status; higher numbers are used क्रम debugging */
#घोषणा AVS_STATUS_MAX		0xff

/* Other AVS related स्थिरants */
#घोषणा AVS_LOOP_LIMIT		10000
#घोषणा AVS_TIMEOUT		300 /* in ms; expected completion is < 10ms */
#घोषणा AVS_FIRMWARE_MAGIC	0xa11600d1

#घोषणा BRCM_AVS_CPUFREQ_PREFIX	"brcmstb-avs"
#घोषणा BRCM_AVS_CPUFREQ_NAME	BRCM_AVS_CPUFREQ_PREFIX "-cpufreq"
#घोषणा BRCM_AVS_CPU_DATA	"brcm,avs-cpu-data-mem"
#घोषणा BRCM_AVS_CPU_INTR	"brcm,avs-cpu-l2-intr"
#घोषणा BRCM_AVS_HOST_INTR	"sw_intr"

काष्ठा pmap अणु
	अचिन्हित पूर्णांक mode;
	अचिन्हित पूर्णांक p1;
	अचिन्हित पूर्णांक p2;
	अचिन्हित पूर्णांक state;
पूर्ण;

काष्ठा निजी_data अणु
	व्योम __iomem *base;
	व्योम __iomem *avs_पूर्णांकr_base;
	काष्ठा device *dev;
	काष्ठा completion करोne;
	काष्ठा semaphore sem;
	काष्ठा pmap pmap;
	पूर्णांक host_irq;
पूर्ण;

अटल व्योम __iomem *__map_region(स्थिर अक्षर *name)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *ptr;

	np = of_find_compatible_node(शून्य, शून्य, name);
	अगर (!np)
		वापस शून्य;

	ptr = of_iomap(np, 0);
	of_node_put(np);

	वापस ptr;
पूर्ण

अटल अचिन्हित दीर्घ रुको_क्रम_avs_command(काष्ठा निजी_data *priv,
					  अचिन्हित दीर्घ समयout)
अणु
	अचिन्हित दीर्घ समय_left = 0;
	u32 val;

	/* Event driven, रुको क्रम the command पूर्णांकerrupt */
	अगर (priv->host_irq >= 0)
		वापस रुको_क्रम_completion_समयout(&priv->करोne,
						   msecs_to_jअगरfies(समयout));

	/* Polling क्रम command completion */
	करो अणु
		समय_left = समयout;
		val = पढ़ोl(priv->base + AVS_MBOX_STATUS);
		अगर (val)
			अवरोध;

		usleep_range(1000, 2000);
	पूर्ण जबतक (--समयout);

	वापस समय_left;
पूर्ण

अटल पूर्णांक __issue_avs_command(काष्ठा निजी_data *priv, अचिन्हित पूर्णांक cmd,
			       अचिन्हित पूर्णांक num_in, अचिन्हित पूर्णांक num_out,
			       u32 args[])
अणु
	व्योम __iomem *base = priv->base;
	अचिन्हित दीर्घ समय_left;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;
	u32 val;

	ret = करोwn_पूर्णांकerruptible(&priv->sem);
	अगर (ret)
		वापस ret;

	/*
	 * Make sure no other command is currently running: cmd is 0 अगर AVS
	 * co-processor is idle. Due to the guard above, we should almost never
	 * have to रुको here.
	 */
	क्रम (i = 0, val = 1; val != 0 && i < AVS_LOOP_LIMIT; i++)
		val = पढ़ोl(base + AVS_MBOX_COMMAND);

	/* Give the caller a chance to retry अगर AVS is busy. */
	अगर (i == AVS_LOOP_LIMIT) अणु
		ret = -EAGAIN;
		जाओ out;
	पूर्ण

	/* Clear status beक्रमe we begin. */
	ग_लिखोl(AVS_STATUS_CLEAR, base + AVS_MBOX_STATUS);

	/* Provide input parameters */
	क्रम (i = 0; i < num_in; i++)
		ग_लिखोl(args[i], base + AVS_MBOX_PARAM(i));

	/* Protect from spurious पूर्णांकerrupts. */
	reinit_completion(&priv->करोne);

	/* Now issue the command & tell firmware to wake up to process it. */
	ग_लिखोl(cmd, base + AVS_MBOX_COMMAND);
	ग_लिखोl(AVS_CPU_L2_INT_MASK, priv->avs_पूर्णांकr_base + AVS_CPU_L2_SET0);

	/* Wait क्रम AVS co-processor to finish processing the command. */
	समय_left = रुको_क्रम_avs_command(priv, AVS_TIMEOUT);

	/*
	 * If the AVS status is not in the expected range, it means AVS didn't
	 * complete our command in समय, and we वापस an error. Also, अगर there
	 * is no "time left", we समयd out रुकोing क्रम the पूर्णांकerrupt.
	 */
	val = पढ़ोl(base + AVS_MBOX_STATUS);
	अगर (समय_left == 0 || val == 0 || val > AVS_STATUS_MAX) अणु
		dev_err(priv->dev, "AVS command %#x didn't complete in time\n",
			cmd);
		dev_err(priv->dev, "    Time left: %u ms, AVS status: %#x\n",
			jअगरfies_to_msecs(समय_left), val);
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	/* Process वापसed values */
	क्रम (i = 0; i < num_out; i++)
		args[i] = पढ़ोl(base + AVS_MBOX_PARAM(i));

	/* Clear status to tell AVS co-processor we are करोne. */
	ग_लिखोl(AVS_STATUS_CLEAR, base + AVS_MBOX_STATUS);

	/* Convert firmware errors to त्रुटि_सं's as much as possible. */
	चयन (val) अणु
	हाल AVS_STATUS_INVALID:
		ret = -EINVAL;
		अवरोध;
	हाल AVS_STATUS_NO_SUPP:
		ret = -ENOTSUPP;
		अवरोध;
	हाल AVS_STATUS_NO_MAP:
		ret = -ENOENT;
		अवरोध;
	हाल AVS_STATUS_MAP_SET:
		ret = -EEXIST;
		अवरोध;
	हाल AVS_STATUS_FAILURE:
		ret = -EIO;
		अवरोध;
	पूर्ण

out:
	up(&priv->sem);

	वापस ret;
पूर्ण

अटल irqवापस_t irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा निजी_data *priv = data;

	/* AVS command completed execution. Wake up __issue_avs_command(). */
	complete(&priv->करोne);

	वापस IRQ_HANDLED;
पूर्ण

अटल अक्षर *brcm_avs_mode_to_string(अचिन्हित पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल AVS_MODE_AVS:
		वापस "AVS";
	हाल AVS_MODE_DFS:
		वापस "DFS";
	हाल AVS_MODE_DVS:
		वापस "DVS";
	हाल AVS_MODE_DVFS:
		वापस "DVFS";
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम brcm_avs_parse_p1(u32 p1, अचिन्हित पूर्णांक *mभाग_p0, अचिन्हित पूर्णांक *pभाग,
			      अचिन्हित पूर्णांक *nभाग)
अणु
	*mभाग_p0 = (p1 >> MDIV_P0_SHIFT) & MDIV_P0_MASK;
	*pभाग = (p1 >> PDIV_SHIFT) & PDIV_MASK;
	*nभाग = (p1 >> NDIV_INT_SHIFT) & NDIV_INT_MASK;
पूर्ण

अटल व्योम brcm_avs_parse_p2(u32 p2, अचिन्हित पूर्णांक *mभाग_p1,
			      अचिन्हित पूर्णांक *mभाग_p2, अचिन्हित पूर्णांक *mभाग_p3,
			      अचिन्हित पूर्णांक *mभाग_p4)
अणु
	*mभाग_p4 = (p2 >> MDIV_P4_SHIFT) & MDIV_P4_MASK;
	*mभाग_p3 = (p2 >> MDIV_P3_SHIFT) & MDIV_P3_MASK;
	*mभाग_p2 = (p2 >> MDIV_P2_SHIFT) & MDIV_P2_MASK;
	*mभाग_p1 = (p2 >> MDIV_P1_SHIFT) & MDIV_P1_MASK;
पूर्ण

अटल पूर्णांक brcm_avs_get_pmap(काष्ठा निजी_data *priv, काष्ठा pmap *pmap)
अणु
	u32 args[AVS_MAX_CMD_ARGS];
	पूर्णांक ret;

	ret = __issue_avs_command(priv, AVS_CMD_GET_PMAP, 0, 4, args);
	अगर (ret || !pmap)
		वापस ret;

	pmap->mode = args[0];
	pmap->p1 = args[1];
	pmap->p2 = args[2];
	pmap->state = args[3];

	वापस 0;
पूर्ण

अटल पूर्णांक brcm_avs_set_pmap(काष्ठा निजी_data *priv, काष्ठा pmap *pmap)
अणु
	u32 args[AVS_MAX_CMD_ARGS];

	args[0] = pmap->mode;
	args[1] = pmap->p1;
	args[2] = pmap->p2;
	args[3] = pmap->state;

	वापस __issue_avs_command(priv, AVS_CMD_SET_PMAP, 4, 0, args);
पूर्ण

अटल पूर्णांक brcm_avs_get_pstate(काष्ठा निजी_data *priv, अचिन्हित पूर्णांक *pstate)
अणु
	u32 args[AVS_MAX_CMD_ARGS];
	पूर्णांक ret;

	ret = __issue_avs_command(priv, AVS_CMD_GET_PSTATE, 0, 1, args);
	अगर (ret)
		वापस ret;
	*pstate = args[0];

	वापस 0;
पूर्ण

अटल पूर्णांक brcm_avs_set_pstate(काष्ठा निजी_data *priv, अचिन्हित पूर्णांक pstate)
अणु
	u32 args[AVS_MAX_CMD_ARGS];

	args[0] = pstate;

	वापस __issue_avs_command(priv, AVS_CMD_SET_PSTATE, 1, 0, args);

पूर्ण

अटल u32 brcm_avs_get_voltage(व्योम __iomem *base)
अणु
	वापस पढ़ोl(base + AVS_MBOX_VOLTAGE1);
पूर्ण

अटल u32 brcm_avs_get_frequency(व्योम __iomem *base)
अणु
	वापस पढ़ोl(base + AVS_MBOX_FREQUENCY) * 1000;	/* in kHz */
पूर्ण

/*
 * We determine which frequencies are supported by cycling through all P-states
 * and पढ़ोing back what frequency we are running at क्रम each P-state.
 */
अटल काष्ठा cpufreq_frequency_table *
brcm_avs_get_freq_table(काष्ठा device *dev, काष्ठा निजी_data *priv)
अणु
	काष्ठा cpufreq_frequency_table *table;
	अचिन्हित पूर्णांक pstate;
	पूर्णांक i, ret;

	/* Remember P-state क्रम later */
	ret = brcm_avs_get_pstate(priv, &pstate);
	अगर (ret)
		वापस ERR_PTR(ret);

	table = devm_kसुस्मृति(dev, AVS_PSTATE_MAX + 1, माप(*table),
			     GFP_KERNEL);
	अगर (!table)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = AVS_PSTATE_P0; i <= AVS_PSTATE_MAX; i++) अणु
		ret = brcm_avs_set_pstate(priv, i);
		अगर (ret)
			वापस ERR_PTR(ret);
		table[i].frequency = brcm_avs_get_frequency(priv->base);
		table[i].driver_data = i;
	पूर्ण
	table[i].frequency = CPUFREQ_TABLE_END;

	/* Restore P-state */
	ret = brcm_avs_set_pstate(priv, pstate);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस table;
पूर्ण

/*
 * To ensure the right firmware is running we need to
 *    - check the MAGIC matches what we expect
 *    - brcm_avs_get_pmap() करोesn't वापस -ENOTSUPP or -EINVAL
 * We need to set up our पूर्णांकerrupt handling beक्रमe calling brcm_avs_get_pmap()!
 */
अटल bool brcm_avs_is_firmware_loaded(काष्ठा निजी_data *priv)
अणु
	u32 magic;
	पूर्णांक rc;

	rc = brcm_avs_get_pmap(priv, शून्य);
	magic = पढ़ोl(priv->base + AVS_MBOX_MAGIC);

	वापस (magic == AVS_FIRMWARE_MAGIC) && ((rc != -ENOTSUPP) ||
		(rc != -EINVAL));
पूर्ण

अटल अचिन्हित पूर्णांक brcm_avs_cpufreq_get(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpufreq_policy *policy = cpufreq_cpu_get(cpu);
	काष्ठा निजी_data *priv = policy->driver_data;

	cpufreq_cpu_put(policy);

	वापस brcm_avs_get_frequency(priv->base);
पूर्ण

अटल पूर्णांक brcm_avs_target_index(काष्ठा cpufreq_policy *policy,
				 अचिन्हित पूर्णांक index)
अणु
	वापस brcm_avs_set_pstate(policy->driver_data,
				  policy->freq_table[index].driver_data);
पूर्ण

अटल पूर्णांक brcm_avs_suspend(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा निजी_data *priv = policy->driver_data;
	पूर्णांक ret;

	ret = brcm_avs_get_pmap(priv, &priv->pmap);
	अगर (ret)
		वापस ret;

	/*
	 * We can't use the P-state वापसed by brcm_avs_get_pmap(), since
	 * that's the initial P-state from when the P-map was करोwnloaded to the
	 * AVS co-processor, not necessarily the P-state we are running at now.
	 * So, we get the current P-state explicitly.
	 */
	ret = brcm_avs_get_pstate(priv, &priv->pmap.state);
	अगर (ret)
		वापस ret;

	/* This is best efक्रमt. Nothing to करो अगर it fails. */
	(व्योम)__issue_avs_command(priv, AVS_CMD_S2_ENTER, 0, 0, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक brcm_avs_resume(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा निजी_data *priv = policy->driver_data;
	पूर्णांक ret;

	/* This is best efक्रमt. Nothing to करो अगर it fails. */
	(व्योम)__issue_avs_command(priv, AVS_CMD_S2_EXIT, 0, 0, शून्य);

	ret = brcm_avs_set_pmap(priv, &priv->pmap);
	अगर (ret == -EEXIST) अणु
		काष्ठा platक्रमm_device *pdev  = cpufreq_get_driver_data();
		काष्ठा device *dev = &pdev->dev;

		dev_warn(dev, "PMAP was already set\n");
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * All initialization code that we only want to execute once goes here. Setup
 * code that can be re-tried on every core (अगर it failed beक्रमe) can go पूर्णांकo
 * brcm_avs_cpufreq_init().
 */
अटल पूर्णांक brcm_avs_prepare_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा निजी_data *priv;
	काष्ठा device *dev;
	पूर्णांक ret;

	dev = &pdev->dev;
	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;
	sema_init(&priv->sem, 1);
	init_completion(&priv->करोne);
	platक्रमm_set_drvdata(pdev, priv);

	priv->base = __map_region(BRCM_AVS_CPU_DATA);
	अगर (!priv->base) अणु
		dev_err(dev, "Couldn't find property %s in device tree.\n",
			BRCM_AVS_CPU_DATA);
		वापस -ENOENT;
	पूर्ण

	priv->avs_पूर्णांकr_base = __map_region(BRCM_AVS_CPU_INTR);
	अगर (!priv->avs_पूर्णांकr_base) अणु
		dev_err(dev, "Couldn't find property %s in device tree.\n",
			BRCM_AVS_CPU_INTR);
		ret = -ENOENT;
		जाओ unmap_base;
	पूर्ण

	priv->host_irq = platक्रमm_get_irq_byname(pdev, BRCM_AVS_HOST_INTR);

	ret = devm_request_irq(dev, priv->host_irq, irq_handler,
			       IRQF_TRIGGER_RISING,
			       BRCM_AVS_HOST_INTR, priv);
	अगर (ret && priv->host_irq >= 0) अणु
		dev_err(dev, "IRQ request failed: %s (%d) -- %d\n",
			BRCM_AVS_HOST_INTR, priv->host_irq, ret);
		जाओ unmap_पूर्णांकr_base;
	पूर्ण

	अगर (brcm_avs_is_firmware_loaded(priv))
		वापस 0;

	dev_err(dev, "AVS firmware is not loaded or doesn't support DVFS\n");
	ret = -ENODEV;

unmap_पूर्णांकr_base:
	iounmap(priv->avs_पूर्णांकr_base);
unmap_base:
	iounmap(priv->base);

	वापस ret;
पूर्ण

अटल व्योम brcm_avs_prepare_uninit(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा निजी_data *priv;

	priv = platक्रमm_get_drvdata(pdev);

	iounmap(priv->avs_पूर्णांकr_base);
	iounmap(priv->base);
पूर्ण

अटल पूर्णांक brcm_avs_cpufreq_init(काष्ठा cpufreq_policy *policy)
अणु
	काष्ठा cpufreq_frequency_table *freq_table;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा निजी_data *priv;
	काष्ठा device *dev;
	पूर्णांक ret;

	pdev = cpufreq_get_driver_data();
	priv = platक्रमm_get_drvdata(pdev);
	policy->driver_data = priv;
	dev = &pdev->dev;

	freq_table = brcm_avs_get_freq_table(dev, priv);
	अगर (IS_ERR(freq_table)) अणु
		ret = PTR_ERR(freq_table);
		dev_err(dev, "Couldn't determine frequency table (%d).\n", ret);
		वापस ret;
	पूर्ण

	policy->freq_table = freq_table;

	/* All cores share the same घड़ी and thus the same policy. */
	cpumask_setall(policy->cpus);

	ret = __issue_avs_command(priv, AVS_CMD_ENABLE, 0, 0, शून्य);
	अगर (!ret) अणु
		अचिन्हित पूर्णांक pstate;

		ret = brcm_avs_get_pstate(priv, &pstate);
		अगर (!ret) अणु
			policy->cur = freq_table[pstate].frequency;
			dev_info(dev, "registered\n");
			वापस 0;
		पूर्ण
	पूर्ण

	dev_err(dev, "couldn't initialize driver (%d)\n", ret);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार show_brcm_avs_pstate(काष्ठा cpufreq_policy *policy, अक्षर *buf)
अणु
	काष्ठा निजी_data *priv = policy->driver_data;
	अचिन्हित पूर्णांक pstate;

	अगर (brcm_avs_get_pstate(priv, &pstate))
		वापस प्र_लिखो(buf, "<unknown>\n");

	वापस प्र_लिखो(buf, "%u\n", pstate);
पूर्ण

अटल sमाप_प्रकार show_brcm_avs_mode(काष्ठा cpufreq_policy *policy, अक्षर *buf)
अणु
	काष्ठा निजी_data *priv = policy->driver_data;
	काष्ठा pmap pmap;

	अगर (brcm_avs_get_pmap(priv, &pmap))
		वापस प्र_लिखो(buf, "<unknown>\n");

	वापस प्र_लिखो(buf, "%s %u\n", brcm_avs_mode_to_string(pmap.mode),
		pmap.mode);
पूर्ण

अटल sमाप_प्रकार show_brcm_avs_pmap(काष्ठा cpufreq_policy *policy, अक्षर *buf)
अणु
	अचिन्हित पूर्णांक mभाग_p0, mभाग_p1, mभाग_p2, mभाग_p3, mभाग_p4;
	काष्ठा निजी_data *priv = policy->driver_data;
	अचिन्हित पूर्णांक nभाग, pभाग;
	काष्ठा pmap pmap;

	अगर (brcm_avs_get_pmap(priv, &pmap))
		वापस प्र_लिखो(buf, "<unknown>\n");

	brcm_avs_parse_p1(pmap.p1, &mभाग_p0, &pभाग, &nभाग);
	brcm_avs_parse_p2(pmap.p2, &mभाग_p1, &mभाग_p2, &mभाग_p3, &mभाग_p4);

	वापस प्र_लिखो(buf, "0x%08x 0x%08x %u %u %u %u %u %u %u %u %u\n",
		pmap.p1, pmap.p2, nभाग, pभाग, mभाग_p0, mभाग_p1, mभाग_p2,
		mभाग_p3, mभाग_p4, pmap.mode, pmap.state);
पूर्ण

अटल sमाप_प्रकार show_brcm_avs_voltage(काष्ठा cpufreq_policy *policy, अक्षर *buf)
अणु
	काष्ठा निजी_data *priv = policy->driver_data;

	वापस प्र_लिखो(buf, "0x%08x\n", brcm_avs_get_voltage(priv->base));
पूर्ण

अटल sमाप_प्रकार show_brcm_avs_frequency(काष्ठा cpufreq_policy *policy, अक्षर *buf)
अणु
	काष्ठा निजी_data *priv = policy->driver_data;

	वापस प्र_लिखो(buf, "0x%08x\n", brcm_avs_get_frequency(priv->base));
पूर्ण

cpufreq_freq_attr_ro(brcm_avs_pstate);
cpufreq_freq_attr_ro(brcm_avs_mode);
cpufreq_freq_attr_ro(brcm_avs_pmap);
cpufreq_freq_attr_ro(brcm_avs_voltage);
cpufreq_freq_attr_ro(brcm_avs_frequency);

अटल काष्ठा freq_attr *brcm_avs_cpufreq_attr[] = अणु
	&cpufreq_freq_attr_scaling_available_freqs,
	&brcm_avs_pstate,
	&brcm_avs_mode,
	&brcm_avs_pmap,
	&brcm_avs_voltage,
	&brcm_avs_frequency,
	शून्य
पूर्ण;

अटल काष्ठा cpufreq_driver brcm_avs_driver = अणु
	.flags		= CPUFREQ_NEED_INITIAL_FREQ_CHECK,
	.verअगरy		= cpufreq_generic_frequency_table_verअगरy,
	.target_index	= brcm_avs_target_index,
	.get		= brcm_avs_cpufreq_get,
	.suspend	= brcm_avs_suspend,
	.resume		= brcm_avs_resume,
	.init		= brcm_avs_cpufreq_init,
	.attr		= brcm_avs_cpufreq_attr,
	.name		= BRCM_AVS_CPUFREQ_PREFIX,
पूर्ण;

अटल पूर्णांक brcm_avs_cpufreq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	ret = brcm_avs_prepare_init(pdev);
	अगर (ret)
		वापस ret;

	brcm_avs_driver.driver_data = pdev;

	ret = cpufreq_रेजिस्टर_driver(&brcm_avs_driver);
	अगर (ret)
		brcm_avs_prepare_uninit(pdev);

	वापस ret;
पूर्ण

अटल पूर्णांक brcm_avs_cpufreq_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	ret = cpufreq_unरेजिस्टर_driver(&brcm_avs_driver);
	WARN_ON(ret);

	brcm_avs_prepare_uninit(pdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id brcm_avs_cpufreq_match[] = अणु
	अणु .compatible = BRCM_AVS_CPU_DATA पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, brcm_avs_cpufreq_match);

अटल काष्ठा platक्रमm_driver brcm_avs_cpufreq_platdrv = अणु
	.driver = अणु
		.name	= BRCM_AVS_CPUFREQ_NAME,
		.of_match_table = brcm_avs_cpufreq_match,
	पूर्ण,
	.probe		= brcm_avs_cpufreq_probe,
	.हटाओ		= brcm_avs_cpufreq_हटाओ,
पूर्ण;
module_platक्रमm_driver(brcm_avs_cpufreq_platdrv);

MODULE_AUTHOR("Markus Mayer <mmayer@broadcom.com>");
MODULE_DESCRIPTION("CPUfreq driver for Broadcom STB AVS");
MODULE_LICENSE("GPL");
