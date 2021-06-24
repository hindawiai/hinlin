<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel(R) Trace Hub Global Trace Hub
 *
 * Copyright (C) 2014-2015 Intel Corporation.
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "intel_th.h"
#समावेश "gth.h"

काष्ठा gth_device;

/**
 * काष्ठा gth_output - GTH view on an output port
 * @gth:	backlink to the GTH device
 * @output:	link to output device's output descriptor
 * @index:	output port number
 * @port_type:	one of GTH_* port type values
 * @master:	biपंचांगap of masters configured क्रम this output
 */
काष्ठा gth_output अणु
	काष्ठा gth_device	*gth;
	काष्ठा पूर्णांकel_th_output	*output;
	अचिन्हित पूर्णांक		index;
	अचिन्हित पूर्णांक		port_type;
	DECLARE_BITMAP(master, TH_CONFIGURABLE_MASTERS + 1);
पूर्ण;

/**
 * काष्ठा gth_device - GTH device
 * @dev:	driver core's device
 * @base:	रेजिस्टर winकरोw base address
 * @output_group:	attributes describing output ports
 * @master_group:	attributes describing master assignments
 * @output:		output ports
 * @master:		master/output port assignments
 * @gth_lock:		serializes accesses to GTH bits
 */
काष्ठा gth_device अणु
	काष्ठा device		*dev;
	व्योम __iomem		*base;

	काष्ठा attribute_group	output_group;
	काष्ठा attribute_group	master_group;
	काष्ठा gth_output	output[TH_POSSIBLE_OUTPUTS];
	चिन्हित अक्षर		master[TH_CONFIGURABLE_MASTERS + 1];
	spinlock_t		gth_lock;
पूर्ण;

अटल व्योम gth_output_set(काष्ठा gth_device *gth, पूर्णांक port,
			   अचिन्हित पूर्णांक config)
अणु
	अचिन्हित दीर्घ reg = port & 4 ? REG_GTH_GTHOPT1 : REG_GTH_GTHOPT0;
	u32 val;
	पूर्णांक shअगरt = (port & 3) * 8;

	val = ioपढ़ो32(gth->base + reg);
	val &= ~(0xff << shअगरt);
	val |= config << shअगरt;
	ioग_लिखो32(val, gth->base + reg);
पूर्ण

अटल अचिन्हित पूर्णांक gth_output_get(काष्ठा gth_device *gth, पूर्णांक port)
अणु
	अचिन्हित दीर्घ reg = port & 4 ? REG_GTH_GTHOPT1 : REG_GTH_GTHOPT0;
	u32 val;
	पूर्णांक shअगरt = (port & 3) * 8;

	val = ioपढ़ो32(gth->base + reg);
	val &= 0xff << shअगरt;
	val >>= shअगरt;

	वापस val;
पूर्ण

अटल व्योम gth_smcfreq_set(काष्ठा gth_device *gth, पूर्णांक port,
			    अचिन्हित पूर्णांक freq)
अणु
	अचिन्हित दीर्घ reg = REG_GTH_SMCR0 + ((port / 2) * 4);
	पूर्णांक shअगरt = (port & 1) * 16;
	u32 val;

	val = ioपढ़ो32(gth->base + reg);
	val &= ~(0xffff << shअगरt);
	val |= freq << shअगरt;
	ioग_लिखो32(val, gth->base + reg);
पूर्ण

अटल अचिन्हित पूर्णांक gth_smcfreq_get(काष्ठा gth_device *gth, पूर्णांक port)
अणु
	अचिन्हित दीर्घ reg = REG_GTH_SMCR0 + ((port / 2) * 4);
	पूर्णांक shअगरt = (port & 1) * 16;
	u32 val;

	val = ioपढ़ो32(gth->base + reg);
	val &= 0xffff << shअगरt;
	val >>= shअगरt;

	वापस val;
पूर्ण

/*
 * "masters" attribute group
 */

काष्ठा master_attribute अणु
	काष्ठा device_attribute	attr;
	काष्ठा gth_device	*gth;
	अचिन्हित पूर्णांक		master;
पूर्ण;

अटल व्योम
gth_master_set(काष्ठा gth_device *gth, अचिन्हित पूर्णांक master, पूर्णांक port)
अणु
	अचिन्हित पूर्णांक reg = REG_GTH_SWDEST0 + ((master >> 1) & ~3u);
	अचिन्हित पूर्णांक shअगरt = (master & 0x7) * 4;
	u32 val;

	अगर (master >= 256) अणु
		reg = REG_GTH_GSWTDEST;
		shअगरt = 0;
	पूर्ण

	val = ioपढ़ो32(gth->base + reg);
	val &= ~(0xf << shअगरt);
	अगर (port >= 0)
		val |= (0x8 | port) << shअगरt;
	ioग_लिखो32(val, gth->base + reg);
पूर्ण

अटल sमाप_प्रकार master_attr_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा master_attribute *ma =
		container_of(attr, काष्ठा master_attribute, attr);
	काष्ठा gth_device *gth = ma->gth;
	माप_प्रकार count;
	पूर्णांक port;

	spin_lock(&gth->gth_lock);
	port = gth->master[ma->master];
	spin_unlock(&gth->gth_lock);

	अगर (port >= 0)
		count = snम_लिखो(buf, PAGE_SIZE, "%x\n", port);
	अन्यथा
		count = snम_लिखो(buf, PAGE_SIZE, "disabled\n");

	वापस count;
पूर्ण

अटल sमाप_प्रकार master_attr_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा master_attribute *ma =
		container_of(attr, काष्ठा master_attribute, attr);
	काष्ठा gth_device *gth = ma->gth;
	पूर्णांक old_port, port;

	अगर (kstrtoपूर्णांक(buf, 10, &port) < 0)
		वापस -EINVAL;

	अगर (port >= TH_POSSIBLE_OUTPUTS || port < -1)
		वापस -EINVAL;

	spin_lock(&gth->gth_lock);

	/* disconnect from the previous output port, अगर any */
	old_port = gth->master[ma->master];
	अगर (old_port >= 0) अणु
		gth->master[ma->master] = -1;
		clear_bit(ma->master, gth->output[old_port].master);

		/*
		 * अगर the port is active, program this setting,
		 * implies that runसमय PM is on
		 */
		अगर (gth->output[old_port].output->active)
			gth_master_set(gth, ma->master, -1);
	पूर्ण

	/* connect to the new output port, अगर any */
	अगर (port >= 0) अणु
		/* check अगर there's a driver क्रम this port */
		अगर (!gth->output[port].output) अणु
			count = -ENODEV;
			जाओ unlock;
		पूर्ण

		set_bit(ma->master, gth->output[port].master);

		/* अगर the port is active, program this setting, see above */
		अगर (gth->output[port].output->active)
			gth_master_set(gth, ma->master, port);
	पूर्ण

	gth->master[ma->master] = port;

unlock:
	spin_unlock(&gth->gth_lock);

	वापस count;
पूर्ण

काष्ठा output_attribute अणु
	काष्ठा device_attribute attr;
	काष्ठा gth_device	*gth;
	अचिन्हित पूर्णांक		port;
	अचिन्हित पूर्णांक		parm;
पूर्ण;

#घोषणा OUTPUT_PARM(_name, _mask, _r, _w, _what)			\
	[TH_OUTPUT_PARM(_name)] = अणु .name = __stringअगरy(_name),		\
				    .get = gth_ ## _what ## _get,	\
				    .set = gth_ ## _what ## _set,	\
				    .mask = (_mask),			\
				    .पढ़ोable = (_r),			\
				    .writable = (_w) पूर्ण

अटल स्थिर काष्ठा output_parm अणु
	स्थिर अक्षर	*name;
	अचिन्हित पूर्णांक	(*get)(काष्ठा gth_device *gth, पूर्णांक port);
	व्योम		(*set)(काष्ठा gth_device *gth, पूर्णांक port,
			       अचिन्हित पूर्णांक val);
	अचिन्हित पूर्णांक	mask;
	अचिन्हित पूर्णांक	पढ़ोable : 1,
			writable : 1;
पूर्ण output_parms[] = अणु
	OUTPUT_PARM(port,	0x7,	1, 0, output),
	OUTPUT_PARM(null,	BIT(3),	1, 1, output),
	OUTPUT_PARM(drop,	BIT(4),	1, 1, output),
	OUTPUT_PARM(reset,	BIT(5),	1, 0, output),
	OUTPUT_PARM(flush,	BIT(7),	0, 1, output),
	OUTPUT_PARM(smcfreq,	0xffff,	1, 1, smcfreq),
पूर्ण;

अटल व्योम
gth_output_parm_set(काष्ठा gth_device *gth, पूर्णांक port, अचिन्हित पूर्णांक parm,
		    अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक config = output_parms[parm].get(gth, port);
	अचिन्हित पूर्णांक mask = output_parms[parm].mask;
	अचिन्हित पूर्णांक shअगरt = __ffs(mask);

	config &= ~mask;
	config |= (val << shअगरt) & mask;
	output_parms[parm].set(gth, port, config);
पूर्ण

अटल अचिन्हित पूर्णांक
gth_output_parm_get(काष्ठा gth_device *gth, पूर्णांक port, अचिन्हित पूर्णांक parm)
अणु
	अचिन्हित पूर्णांक config = output_parms[parm].get(gth, port);
	अचिन्हित पूर्णांक mask = output_parms[parm].mask;
	अचिन्हित पूर्णांक shअगरt = __ffs(mask);

	config &= mask;
	config >>= shअगरt;
	वापस config;
पूर्ण

/*
 * Reset outमाला_दो and sources
 */
अटल पूर्णांक पूर्णांकel_th_gth_reset(काष्ठा gth_device *gth)
अणु
	u32 reg;
	पूर्णांक port, i;

	reg = ioपढ़ो32(gth->base + REG_GTH_SCRPD0);
	अगर (reg & SCRPD_DEBUGGER_IN_USE)
		वापस -EBUSY;

	/* Always save/restore STH and TU रेजिस्टरs in S0ix entry/निकास */
	reg |= SCRPD_STH_IS_ENABLED | SCRPD_TRIGGER_IS_ENABLED;
	ioग_लिखो32(reg, gth->base + REG_GTH_SCRPD0);

	/* output ports */
	क्रम (port = 0; port < 8; port++) अणु
		अगर (gth_output_parm_get(gth, port, TH_OUTPUT_PARM(port)) ==
		    GTH_NONE)
			जारी;

		gth_output_set(gth, port, 0);
		gth_smcfreq_set(gth, port, 16);
	पूर्ण
	/* disable overrides */
	ioग_लिखो32(0, gth->base + REG_GTH_DESTOVR);

	/* masters swdest_0~31 and gswdest */
	क्रम (i = 0; i < 33; i++)
		ioग_लिखो32(0, gth->base + REG_GTH_SWDEST0 + i * 4);

	/* sources */
	ioग_लिखो32(0, gth->base + REG_GTH_SCR);
	ioग_लिखो32(0xfc, gth->base + REG_GTH_SCR2);

	/* setup CTS क्रम single trigger */
	ioग_लिखो32(CTS_EVENT_ENABLE_IF_ANYTHING, gth->base + REG_CTS_C0S0_EN);
	ioग_लिखो32(CTS_ACTION_CONTROL_SET_STATE(CTS_STATE_IDLE) |
		  CTS_ACTION_CONTROL_TRIGGER, gth->base + REG_CTS_C0S0_ACT);

	वापस 0;
पूर्ण

/*
 * "outputs" attribute group
 */

अटल sमाप_प्रकार output_attr_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा output_attribute *oa =
		container_of(attr, काष्ठा output_attribute, attr);
	काष्ठा gth_device *gth = oa->gth;
	माप_प्रकार count;

	pm_runसमय_get_sync(dev);

	spin_lock(&gth->gth_lock);
	count = snम_लिखो(buf, PAGE_SIZE, "%x\n",
			 gth_output_parm_get(gth, oa->port, oa->parm));
	spin_unlock(&gth->gth_lock);

	pm_runसमय_put(dev);

	वापस count;
पूर्ण

अटल sमाप_प्रकार output_attr_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा output_attribute *oa =
		container_of(attr, काष्ठा output_attribute, attr);
	काष्ठा gth_device *gth = oa->gth;
	अचिन्हित पूर्णांक config;

	अगर (kstrtouपूर्णांक(buf, 16, &config) < 0)
		वापस -EINVAL;

	pm_runसमय_get_sync(dev);

	spin_lock(&gth->gth_lock);
	gth_output_parm_set(gth, oa->port, oa->parm, config);
	spin_unlock(&gth->gth_lock);

	pm_runसमय_put(dev);

	वापस count;
पूर्ण

अटल पूर्णांक पूर्णांकel_th_master_attributes(काष्ठा gth_device *gth)
अणु
	काष्ठा master_attribute *master_attrs;
	काष्ठा attribute **attrs;
	पूर्णांक i, nattrs = TH_CONFIGURABLE_MASTERS + 2;

	attrs = devm_kसुस्मृति(gth->dev, nattrs, माप(व्योम *), GFP_KERNEL);
	अगर (!attrs)
		वापस -ENOMEM;

	master_attrs = devm_kसुस्मृति(gth->dev, nattrs,
				    माप(काष्ठा master_attribute),
				    GFP_KERNEL);
	अगर (!master_attrs)
		वापस -ENOMEM;

	क्रम (i = 0; i < TH_CONFIGURABLE_MASTERS + 1; i++) अणु
		अक्षर *name;

		name = devm_kaप्र_लिखो(gth->dev, GFP_KERNEL, "%d%s", i,
				      i == TH_CONFIGURABLE_MASTERS ? "+" : "");
		अगर (!name)
			वापस -ENOMEM;

		master_attrs[i].attr.attr.name = name;
		master_attrs[i].attr.attr.mode = S_IRUGO | S_IWUSR;
		master_attrs[i].attr.show = master_attr_show;
		master_attrs[i].attr.store = master_attr_store;

		sysfs_attr_init(&master_attrs[i].attr.attr);
		attrs[i] = &master_attrs[i].attr.attr;

		master_attrs[i].gth = gth;
		master_attrs[i].master = i;
	पूर्ण

	gth->master_group.name	= "masters";
	gth->master_group.attrs = attrs;

	वापस sysfs_create_group(&gth->dev->kobj, &gth->master_group);
पूर्ण

अटल पूर्णांक पूर्णांकel_th_output_attributes(काष्ठा gth_device *gth)
अणु
	काष्ठा output_attribute *out_attrs;
	काष्ठा attribute **attrs;
	पूर्णांक i, j, nouts = TH_POSSIBLE_OUTPUTS;
	पूर्णांक nparms = ARRAY_SIZE(output_parms);
	पूर्णांक nattrs = nouts * nparms + 1;

	attrs = devm_kसुस्मृति(gth->dev, nattrs, माप(व्योम *), GFP_KERNEL);
	अगर (!attrs)
		वापस -ENOMEM;

	out_attrs = devm_kसुस्मृति(gth->dev, nattrs,
				 माप(काष्ठा output_attribute),
				 GFP_KERNEL);
	अगर (!out_attrs)
		वापस -ENOMEM;

	क्रम (i = 0; i < nouts; i++) अणु
		क्रम (j = 0; j < nparms; j++) अणु
			अचिन्हित पूर्णांक idx = i * nparms + j;
			अक्षर *name;

			name = devm_kaप्र_लिखो(gth->dev, GFP_KERNEL, "%d_%s", i,
					      output_parms[j].name);
			अगर (!name)
				वापस -ENOMEM;

			out_attrs[idx].attr.attr.name = name;

			अगर (output_parms[j].पढ़ोable) अणु
				out_attrs[idx].attr.attr.mode |= S_IRUGO;
				out_attrs[idx].attr.show = output_attr_show;
			पूर्ण

			अगर (output_parms[j].writable) अणु
				out_attrs[idx].attr.attr.mode |= S_IWUSR;
				out_attrs[idx].attr.store = output_attr_store;
			पूर्ण

			sysfs_attr_init(&out_attrs[idx].attr.attr);
			attrs[idx] = &out_attrs[idx].attr.attr;

			out_attrs[idx].gth = gth;
			out_attrs[idx].port = i;
			out_attrs[idx].parm = j;
		पूर्ण
	पूर्ण

	gth->output_group.name	= "outputs";
	gth->output_group.attrs = attrs;

	वापस sysfs_create_group(&gth->dev->kobj, &gth->output_group);
पूर्ण

/**
 * पूर्णांकel_th_gth_stop() - stop tracing to an output device
 * @gth:		GTH device
 * @output:		output device's descriptor
 * @capture_करोne:	set when no more traces will be captured
 *
 * This will stop tracing using क्रमce storeEn off संकेत and रुको क्रम the
 * pipelines to be empty क्रम the corresponding output port.
 */
अटल व्योम पूर्णांकel_th_gth_stop(काष्ठा gth_device *gth,
			      काष्ठा पूर्णांकel_th_output *output,
			      bool capture_करोne)
अणु
	काष्ठा पूर्णांकel_th_device *outdev =
		container_of(output, काष्ठा पूर्णांकel_th_device, output);
	काष्ठा पूर्णांकel_th_driver *outdrv =
		to_पूर्णांकel_th_driver(outdev->dev.driver);
	अचिन्हित दीर्घ count;
	u32 reg;
	u32 scr2 = 0xfc | (capture_करोne ? 1 : 0);

	ioग_लिखो32(0, gth->base + REG_GTH_SCR);
	ioग_लिखो32(scr2, gth->base + REG_GTH_SCR2);

	/* रुको on pipeline empty क्रम the given port */
	क्रम (reg = 0, count = GTH_PLE_WAITLOOP_DEPTH;
	     count && !(reg & BIT(output->port)); count--) अणु
		reg = ioपढ़ो32(gth->base + REG_GTH_STAT);
		cpu_relax();
	पूर्ण

	अगर (!count)
		dev_dbg(gth->dev, "timeout waiting for GTH[%d] PLE\n",
			output->port);

	/* रुको on output piepline empty */
	अगर (outdrv->रुको_empty)
		outdrv->रुको_empty(outdev);

	/* clear क्रमce capture करोne क्रम next captures */
	ioग_लिखो32(0xfc, gth->base + REG_GTH_SCR2);
पूर्ण

/**
 * पूर्णांकel_th_gth_start() - start tracing to an output device
 * @gth:	GTH device
 * @output:	output device's descriptor
 *
 * This will start tracing using क्रमce storeEn संकेत.
 */
अटल व्योम पूर्णांकel_th_gth_start(काष्ठा gth_device *gth,
			       काष्ठा पूर्णांकel_th_output *output)
अणु
	u32 scr = 0xfc0000;

	अगर (output->multiblock)
		scr |= 0xff;

	ioग_लिखो32(scr, gth->base + REG_GTH_SCR);
	ioग_लिखो32(0, gth->base + REG_GTH_SCR2);
पूर्ण

/**
 * पूर्णांकel_th_gth_disable() - disable tracing to an output device
 * @thdev:	GTH device
 * @output:	output device's descriptor
 *
 * This will deconfigure all masters set to output to this device,
 * disable tracing using क्रमce storeEn off संकेत and रुको क्रम the
 * "pipeline empty" bit क्रम corresponding output port.
 */
अटल व्योम पूर्णांकel_th_gth_disable(काष्ठा पूर्णांकel_th_device *thdev,
				 काष्ठा पूर्णांकel_th_output *output)
अणु
	काष्ठा gth_device *gth = dev_get_drvdata(&thdev->dev);
	पूर्णांक master;
	u32 reg;

	spin_lock(&gth->gth_lock);
	output->active = false;

	क्रम_each_set_bit(master, gth->output[output->port].master,
			 TH_CONFIGURABLE_MASTERS + 1) अणु
		gth_master_set(gth, master, -1);
	पूर्ण
	spin_unlock(&gth->gth_lock);

	पूर्णांकel_th_gth_stop(gth, output, true);

	reg = ioपढ़ो32(gth->base + REG_GTH_SCRPD0);
	reg &= ~output->scratchpad;
	ioग_लिखो32(reg, gth->base + REG_GTH_SCRPD0);
पूर्ण

अटल व्योम gth_tscu_resync(काष्ठा gth_device *gth)
अणु
	u32 reg;

	reg = ioपढ़ो32(gth->base + REG_TSCU_TSUCTRL);
	reg &= ~TSUCTRL_CTCRESYNC;
	ioग_लिखो32(reg, gth->base + REG_TSCU_TSUCTRL);
पूर्ण

/**
 * पूर्णांकel_th_gth_enable() - enable tracing to an output device
 * @thdev:	GTH device
 * @output:	output device's descriptor
 *
 * This will configure all masters set to output to this device and
 * enable tracing using क्रमce storeEn संकेत.
 */
अटल व्योम पूर्णांकel_th_gth_enable(काष्ठा पूर्णांकel_th_device *thdev,
				काष्ठा पूर्णांकel_th_output *output)
अणु
	काष्ठा gth_device *gth = dev_get_drvdata(&thdev->dev);
	काष्ठा पूर्णांकel_th *th = to_पूर्णांकel_th(thdev);
	पूर्णांक master;
	u32 scrpd;

	spin_lock(&gth->gth_lock);
	क्रम_each_set_bit(master, gth->output[output->port].master,
			 TH_CONFIGURABLE_MASTERS + 1) अणु
		gth_master_set(gth, master, output->port);
	पूर्ण

	output->active = true;
	spin_unlock(&gth->gth_lock);

	अगर (INTEL_TH_CAP(th, tscu_enable))
		gth_tscu_resync(gth);

	scrpd = ioपढ़ो32(gth->base + REG_GTH_SCRPD0);
	scrpd |= output->scratchpad;
	ioग_लिखो32(scrpd, gth->base + REG_GTH_SCRPD0);

	पूर्णांकel_th_gth_start(gth, output);
पूर्ण

/**
 * पूर्णांकel_th_gth_चयन() - execute a चयन sequence
 * @thdev:	GTH device
 * @output:	output device's descriptor
 *
 * This will execute a चयन sequence that will trigger a चयन winकरोw
 * when tracing to MSC in multi-block mode.
 */
अटल व्योम पूर्णांकel_th_gth_चयन(काष्ठा पूर्णांकel_th_device *thdev,
				काष्ठा पूर्णांकel_th_output *output)
अणु
	काष्ठा gth_device *gth = dev_get_drvdata(&thdev->dev);
	अचिन्हित दीर्घ count;
	u32 reg;

	/* trigger */
	ioग_लिखो32(0, gth->base + REG_CTS_CTL);
	ioग_लिखो32(CTS_CTL_SEQUENCER_ENABLE, gth->base + REG_CTS_CTL);
	/* रुको on trigger status */
	क्रम (reg = 0, count = CTS_TRIG_WAITLOOP_DEPTH;
	     count && !(reg & BIT(4)); count--) अणु
		reg = ioपढ़ो32(gth->base + REG_CTS_STAT);
		cpu_relax();
	पूर्ण
	अगर (!count)
		dev_dbg(&thdev->dev, "timeout waiting for CTS Trigger\n");

	/* De-निश्चित the trigger */
	ioग_लिखो32(0, gth->base + REG_CTS_CTL);

	पूर्णांकel_th_gth_stop(gth, output, false);
	पूर्णांकel_th_gth_start(gth, output);
पूर्ण

/**
 * पूर्णांकel_th_gth_assign() - assign output device to a GTH output port
 * @thdev:	GTH device
 * @othdev:	output device
 *
 * This will match a given output device parameters against present
 * output ports on the GTH and fill out relevant bits in output device's
 * descriptor.
 *
 * Return:	0 on success, -त्रुटि_सं on error.
 */
अटल पूर्णांक पूर्णांकel_th_gth_assign(काष्ठा पूर्णांकel_th_device *thdev,
			       काष्ठा पूर्णांकel_th_device *othdev)
अणु
	काष्ठा gth_device *gth = dev_get_drvdata(&thdev->dev);
	पूर्णांक i, id;

	अगर (thdev->host_mode)
		वापस -EBUSY;

	अगर (othdev->type != INTEL_TH_OUTPUT)
		वापस -EINVAL;

	क्रम (i = 0, id = 0; i < TH_POSSIBLE_OUTPUTS; i++) अणु
		अगर (gth->output[i].port_type != othdev->output.type)
			जारी;

		अगर (othdev->id == -1 || othdev->id == id)
			जाओ found;

		id++;
	पूर्ण

	वापस -ENOENT;

found:
	spin_lock(&gth->gth_lock);
	othdev->output.port = i;
	othdev->output.active = false;
	gth->output[i].output = &othdev->output;
	spin_unlock(&gth->gth_lock);

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_th_gth_unassign() - deassociate an output device from its output port
 * @thdev:	GTH device
 * @othdev:	output device
 */
अटल व्योम पूर्णांकel_th_gth_unassign(काष्ठा पूर्णांकel_th_device *thdev,
				  काष्ठा पूर्णांकel_th_device *othdev)
अणु
	काष्ठा gth_device *gth = dev_get_drvdata(&thdev->dev);
	पूर्णांक port = othdev->output.port;
	पूर्णांक master;

	अगर (thdev->host_mode)
		वापस;

	spin_lock(&gth->gth_lock);
	othdev->output.port = -1;
	othdev->output.active = false;
	gth->output[port].output = शून्य;
	क्रम (master = 0; master < TH_CONFIGURABLE_MASTERS + 1; master++)
		अगर (gth->master[master] == port)
			gth->master[master] = -1;
	spin_unlock(&gth->gth_lock);
पूर्ण

अटल पूर्णांक
पूर्णांकel_th_gth_set_output(काष्ठा पूर्णांकel_th_device *thdev, अचिन्हित पूर्णांक master)
अणु
	काष्ठा gth_device *gth = dev_get_drvdata(&thdev->dev);
	पूर्णांक port = 0; /* FIXME: make शेष output configurable */

	/*
	 * everything above TH_CONFIGURABLE_MASTERS is controlled by the
	 * same रेजिस्टर
	 */
	अगर (master > TH_CONFIGURABLE_MASTERS)
		master = TH_CONFIGURABLE_MASTERS;

	spin_lock(&gth->gth_lock);
	अगर (gth->master[master] == -1) अणु
		set_bit(master, gth->output[port].master);
		gth->master[master] = port;
	पूर्ण
	spin_unlock(&gth->gth_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_th_gth_probe(काष्ठा पूर्णांकel_th_device *thdev)
अणु
	काष्ठा device *dev = &thdev->dev;
	काष्ठा पूर्णांकel_th *th = dev_get_drvdata(dev->parent);
	काष्ठा gth_device *gth;
	काष्ठा resource *res;
	व्योम __iomem *base;
	पूर्णांक i, ret;

	res = पूर्णांकel_th_device_get_resource(thdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	base = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!base)
		वापस -ENOMEM;

	gth = devm_kzalloc(dev, माप(*gth), GFP_KERNEL);
	अगर (!gth)
		वापस -ENOMEM;

	gth->dev = dev;
	gth->base = base;
	spin_lock_init(&gth->gth_lock);

	dev_set_drvdata(dev, gth);

	/*
	 * Host mode can be संकेतled via SW means or via SCRPD_DEBUGGER_IN_USE
	 * bit. Either way, करोn't reset HW in this case, and don't export any
	 * capture configuration attributes. Also, refuse to assign output
	 * drivers to ports, see पूर्णांकel_th_gth_assign().
	 */
	अगर (thdev->host_mode)
		वापस 0;

	ret = पूर्णांकel_th_gth_reset(gth);
	अगर (ret) अणु
		अगर (ret != -EBUSY)
			वापस ret;

		thdev->host_mode = true;

		वापस 0;
	पूर्ण

	क्रम (i = 0; i < TH_CONFIGURABLE_MASTERS + 1; i++)
		gth->master[i] = -1;

	क्रम (i = 0; i < TH_POSSIBLE_OUTPUTS; i++) अणु
		gth->output[i].gth = gth;
		gth->output[i].index = i;
		gth->output[i].port_type =
			gth_output_parm_get(gth, i, TH_OUTPUT_PARM(port));
		अगर (gth->output[i].port_type == GTH_NONE)
			जारी;

		ret = पूर्णांकel_th_output_enable(th, gth->output[i].port_type);
		/* -ENODEV is ok, we just won't have that device क्रमागतerated */
		अगर (ret && ret != -ENODEV)
			वापस ret;
	पूर्ण

	अगर (पूर्णांकel_th_output_attributes(gth) ||
	    पूर्णांकel_th_master_attributes(gth)) अणु
		pr_warn("Can't initialize sysfs attributes\n");

		अगर (gth->output_group.attrs)
			sysfs_हटाओ_group(&gth->dev->kobj, &gth->output_group);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_th_gth_हटाओ(काष्ठा पूर्णांकel_th_device *thdev)
अणु
	काष्ठा gth_device *gth = dev_get_drvdata(&thdev->dev);

	sysfs_हटाओ_group(&gth->dev->kobj, &gth->output_group);
	sysfs_हटाओ_group(&gth->dev->kobj, &gth->master_group);
पूर्ण

अटल काष्ठा पूर्णांकel_th_driver पूर्णांकel_th_gth_driver = अणु
	.probe		= पूर्णांकel_th_gth_probe,
	.हटाओ		= पूर्णांकel_th_gth_हटाओ,
	.assign		= पूर्णांकel_th_gth_assign,
	.unassign	= पूर्णांकel_th_gth_unassign,
	.set_output	= पूर्णांकel_th_gth_set_output,
	.enable		= पूर्णांकel_th_gth_enable,
	.trig_चयन	= पूर्णांकel_th_gth_चयन,
	.disable	= पूर्णांकel_th_gth_disable,
	.driver	= अणु
		.name	= "gth",
		.owner	= THIS_MODULE,
	पूर्ण,
पूर्ण;

module_driver(पूर्णांकel_th_gth_driver,
	      पूर्णांकel_th_driver_रेजिस्टर,
	      पूर्णांकel_th_driver_unरेजिस्टर);

MODULE_ALIAS("intel_th_switch");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel(R) Trace Hub Global Trace Hub driver");
MODULE_AUTHOR("Alexander Shishkin <alexander.shishkin@linux.intel.com>");
