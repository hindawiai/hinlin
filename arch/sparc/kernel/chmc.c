<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* chmc.c: Driver क्रम UltraSPARC-III memory controller.
 *
 * Copyright (C) 2001, 2007, 2008 David S. Miller (davem@davemloft.net)
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/माला.स>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <यंत्र/spitfire.h>
#समावेश <यंत्र/chmctrl.h>
#समावेश <यंत्र/cpudata.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/head.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/memctrl.h>

#घोषणा DRV_MODULE_NAME		"chmc"
#घोषणा PFX DRV_MODULE_NAME	": "
#घोषणा DRV_MODULE_VERSION	"0.2"

MODULE_AUTHOR("David S. Miller (davem@davemloft.net)");
MODULE_DESCRIPTION("UltraSPARC-III memory controller driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_MODULE_VERSION);

अटल पूर्णांक mc_type;
#घोषणा MC_TYPE_SAFARI		1
#घोषणा MC_TYPE_JBUS		2

अटल dimm_prपूर्णांकer_t us3mc_dimm_prपूर्णांकer;

#घोषणा CHMCTRL_NDGRPS	2
#घोषणा CHMCTRL_NDIMMS	4

#घोषणा CHMC_DIMMS_PER_MC	(CHMCTRL_NDGRPS * CHMCTRL_NDIMMS)

/* OBP memory-layout property क्रमmat. */
काष्ठा chmc_obp_map अणु
	अचिन्हित अक्षर	dimm_map[144];
	अचिन्हित अक्षर	pin_map[576];
पूर्ण;

#घोषणा DIMM_LABEL_SZ	8

काष्ठा chmc_obp_mem_layout अणु
	/* One max 8-byte string label per DIMM.  Usually
	 * this matches the label on the motherboard where
	 * that DIMM resides.
	 */
	अक्षर			dimm_labels[CHMC_DIMMS_PER_MC][DIMM_LABEL_SZ];

	/* If symmetric use map[0], अन्यथा it is
	 * asymmetric and map[1] should be used.
	 */
	अक्षर			symmetric;

	काष्ठा chmc_obp_map	map[2];
पूर्ण;

#घोषणा CHMCTRL_NBANKS	4

काष्ठा chmc_bank_info अणु
	काष्ठा chmc		*p;
	पूर्णांक			bank_id;

	u64			raw_reg;
	पूर्णांक			valid;
	पूर्णांक			uk;
	पूर्णांक			um;
	पूर्णांक			lk;
	पूर्णांक			lm;
	पूर्णांक			पूर्णांकerleave;
	अचिन्हित दीर्घ		base;
	अचिन्हित दीर्घ		size;
पूर्ण;

काष्ठा chmc अणु
	काष्ठा list_head		list;
	पूर्णांक				portid;

	काष्ठा chmc_obp_mem_layout	layout_prop;
	पूर्णांक				layout_size;

	व्योम __iomem			*regs;

	u64				timing_control1;
	u64				timing_control2;
	u64				timing_control3;
	u64				timing_control4;
	u64				memaddr_control;

	काष्ठा chmc_bank_info		logical_banks[CHMCTRL_NBANKS];
पूर्ण;

#घोषणा JBUSMC_REGS_SIZE		8

#घोषणा JB_MC_REG1_DIMM2_BANK3		0x8000000000000000UL
#घोषणा JB_MC_REG1_DIMM1_BANK1		0x4000000000000000UL
#घोषणा JB_MC_REG1_DIMM2_BANK2		0x2000000000000000UL
#घोषणा JB_MC_REG1_DIMM1_BANK0		0x1000000000000000UL
#घोषणा JB_MC_REG1_XOR			0x0000010000000000UL
#घोषणा JB_MC_REG1_ADDR_GEN_2		0x000000e000000000UL
#घोषणा JB_MC_REG1_ADDR_GEN_2_SHIFT	37
#घोषणा JB_MC_REG1_ADDR_GEN_1		0x0000001c00000000UL
#घोषणा JB_MC_REG1_ADDR_GEN_1_SHIFT	34
#घोषणा JB_MC_REG1_INTERLEAVE		0x0000000001800000UL
#घोषणा JB_MC_REG1_INTERLEAVE_SHIFT	23
#घोषणा JB_MC_REG1_DIMM2_PTYPE		0x0000000000200000UL
#घोषणा JB_MC_REG1_DIMM2_PTYPE_SHIFT	21
#घोषणा JB_MC_REG1_DIMM1_PTYPE		0x0000000000100000UL
#घोषणा JB_MC_REG1_DIMM1_PTYPE_SHIFT	20

#घोषणा PART_TYPE_X8		0
#घोषणा PART_TYPE_X4		1

#घोषणा INTERLEAVE_NONE		0
#घोषणा INTERLEAVE_SAME		1
#घोषणा INTERLEAVE_INTERNAL	2
#घोषणा INTERLEAVE_BOTH		3

#घोषणा ADDR_GEN_128MB		0
#घोषणा ADDR_GEN_256MB		1
#घोषणा ADDR_GEN_512MB		2
#घोषणा ADDR_GEN_1GB		3

#घोषणा JB_NUM_DIMM_GROUPS	2
#घोषणा JB_NUM_DIMMS_PER_GROUP	2
#घोषणा JB_NUM_DIMMS		(JB_NUM_DIMM_GROUPS * JB_NUM_DIMMS_PER_GROUP)

काष्ठा jbusmc_obp_map अणु
	अचिन्हित अक्षर	dimm_map[18];
	अचिन्हित अक्षर	pin_map[144];
पूर्ण;

काष्ठा jbusmc_obp_mem_layout अणु
	/* One max 8-byte string label per DIMM.  Usually
	 * this matches the label on the motherboard where
	 * that DIMM resides.
	 */
	अक्षर		dimm_labels[JB_NUM_DIMMS][DIMM_LABEL_SZ];

	/* If symmetric use map[0], अन्यथा it is
	 * asymmetric and map[1] should be used.
	 */
	अक्षर			symmetric;

	काष्ठा jbusmc_obp_map	map;

	अक्षर			_pad;
पूर्ण;

काष्ठा jbusmc_dimm_group अणु
	काष्ठा jbusmc			*controller;
	पूर्णांक				index;
	u64				base_addr;
	u64				size;
पूर्ण;

काष्ठा jbusmc अणु
	व्योम __iomem			*regs;
	u64				mc_reg_1;
	u32				portid;
	काष्ठा jbusmc_obp_mem_layout	layout;
	पूर्णांक				layout_len;
	पूर्णांक				num_dimm_groups;
	काष्ठा jbusmc_dimm_group	dimm_groups[JB_NUM_DIMM_GROUPS];
	काष्ठा list_head		list;
पूर्ण;

अटल DEFINE_SPINLOCK(mctrl_list_lock);
अटल LIST_HEAD(mctrl_list);

अटल व्योम mc_list_add(काष्ठा list_head *list)
अणु
	spin_lock(&mctrl_list_lock);
	list_add(list, &mctrl_list);
	spin_unlock(&mctrl_list_lock);
पूर्ण

अटल व्योम mc_list_del(काष्ठा list_head *list)
अणु
	spin_lock(&mctrl_list_lock);
	list_del_init(list);
	spin_unlock(&mctrl_list_lock);
पूर्ण

#घोषणा SYNDROME_MIN	-1
#घोषणा SYNDROME_MAX	144

/* Covert syndrome code पूर्णांकo the way the bits are positioned
 * on the bus.
 */
अटल पूर्णांक syndrome_to_qword_code(पूर्णांक syndrome_code)
अणु
	अगर (syndrome_code < 128)
		syndrome_code += 16;
	अन्यथा अगर (syndrome_code < 128 + 9)
		syndrome_code -= (128 - 7);
	अन्यथा अगर (syndrome_code < (128 + 9 + 3))
		syndrome_code -= (128 + 9 - 4);
	अन्यथा
		syndrome_code -= (128 + 9 + 3);
	वापस syndrome_code;
पूर्ण

/* All this magic has to करो with how a cache line comes over the wire
 * on Safari and JBUS.  A 64-bit line comes over in 1 or more quadword
 * cycles, each of which transmit ECC/MTAG info as well as the actual
 * data.
 */
#घोषणा L2_LINE_SIZE		64
#घोषणा L2_LINE_ADDR_MSK	(L2_LINE_SIZE - 1)
#घोषणा QW_PER_LINE		4
#घोषणा QW_BYTES		(L2_LINE_SIZE / QW_PER_LINE)
#घोषणा QW_BITS			144
#घोषणा SAFARI_LAST_BIT		(576 - 1)
#घोषणा JBUS_LAST_BIT		(144 - 1)

अटल व्योम get_pin_and_dimm_str(पूर्णांक syndrome_code, अचिन्हित दीर्घ paddr,
				 पूर्णांक *pin_p, अक्षर **dimm_str_p, व्योम *_prop,
				 पूर्णांक base_dimm_offset)
अणु
	पूर्णांक qword_code = syndrome_to_qword_code(syndrome_code);
	पूर्णांक cache_line_offset;
	पूर्णांक offset_inverse;
	पूर्णांक dimm_map_index;
	पूर्णांक map_val;

	अगर (mc_type == MC_TYPE_JBUS) अणु
		काष्ठा jbusmc_obp_mem_layout *p = _prop;

		/* JBUS */
		cache_line_offset = qword_code;
		offset_inverse = (JBUS_LAST_BIT - cache_line_offset);
		dimm_map_index = offset_inverse / 8;
		map_val = p->map.dimm_map[dimm_map_index];
		map_val = ((map_val >> ((7 - (offset_inverse & 7)))) & 1);
		*dimm_str_p = p->dimm_labels[base_dimm_offset + map_val];
		*pin_p = p->map.pin_map[cache_line_offset];
	पूर्ण अन्यथा अणु
		काष्ठा chmc_obp_mem_layout *p = _prop;
		काष्ठा chmc_obp_map *mp;
		पूर्णांक qword;

		/* Safari */
		अगर (p->symmetric)
			mp = &p->map[0];
		अन्यथा
			mp = &p->map[1];

		qword = (paddr & L2_LINE_ADDR_MSK) / QW_BYTES;
		cache_line_offset = ((3 - qword) * QW_BITS) + qword_code;
		offset_inverse = (SAFARI_LAST_BIT - cache_line_offset);
		dimm_map_index = offset_inverse >> 2;
		map_val = mp->dimm_map[dimm_map_index];
		map_val = ((map_val >> ((3 - (offset_inverse & 3)) << 1)) & 0x3);
		*dimm_str_p = p->dimm_labels[base_dimm_offset + map_val];
		*pin_p = mp->pin_map[cache_line_offset];
	पूर्ण
पूर्ण

अटल काष्ठा jbusmc_dimm_group *jbusmc_find_dimm_group(अचिन्हित दीर्घ phys_addr)
अणु
	काष्ठा jbusmc *p;

	list_क्रम_each_entry(p, &mctrl_list, list) अणु
		पूर्णांक i;

		क्रम (i = 0; i < p->num_dimm_groups; i++) अणु
			काष्ठा jbusmc_dimm_group *dp = &p->dimm_groups[i];

			अगर (phys_addr < dp->base_addr ||
			    (dp->base_addr + dp->size) <= phys_addr)
				जारी;

			वापस dp;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक jbusmc_prपूर्णांक_dimm(पूर्णांक syndrome_code,
			     अचिन्हित दीर्घ phys_addr,
			     अक्षर *buf, पूर्णांक buflen)
अणु
	काष्ठा jbusmc_obp_mem_layout *prop;
	काष्ठा jbusmc_dimm_group *dp;
	काष्ठा jbusmc *p;
	पूर्णांक first_dimm;

	dp = jbusmc_find_dimm_group(phys_addr);
	अगर (dp == शून्य ||
	    syndrome_code < SYNDROME_MIN ||
	    syndrome_code > SYNDROME_MAX) अणु
		buf[0] = '?';
		buf[1] = '?';
		buf[2] = '?';
		buf[3] = '\0';
		वापस 0;
	पूर्ण
	p = dp->controller;
	prop = &p->layout;

	first_dimm = dp->index * JB_NUM_DIMMS_PER_GROUP;

	अगर (syndrome_code != SYNDROME_MIN) अणु
		अक्षर *dimm_str;
		पूर्णांक pin;

		get_pin_and_dimm_str(syndrome_code, phys_addr, &pin,
				     &dimm_str, prop, first_dimm);
		प्र_लिखो(buf, "%s, pin %3d", dimm_str, pin);
	पूर्ण अन्यथा अणु
		पूर्णांक dimm;

		/* Multi-bit error, we just dump out all the
		 * dimm labels associated with this dimm group.
		 */
		क्रम (dimm = 0; dimm < JB_NUM_DIMMS_PER_GROUP; dimm++) अणु
			प्र_लिखो(buf, "%s ",
				prop->dimm_labels[first_dimm + dimm]);
			buf += म_माप(buf);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल u64 jbusmc_dimm_group_size(u64 base,
				  स्थिर काष्ठा linux_prom64_रेजिस्टरs *mem_regs,
				  पूर्णांक num_mem_regs)
अणु
	u64 max = base + (8UL * 1024 * 1024 * 1024);
	u64 max_seen = base;
	पूर्णांक i;

	क्रम (i = 0; i < num_mem_regs; i++) अणु
		स्थिर काष्ठा linux_prom64_रेजिस्टरs *ent;
		u64 this_base;
		u64 this_end;

		ent = &mem_regs[i];
		this_base = ent->phys_addr;
		this_end = this_base + ent->reg_size;
		अगर (base < this_base || base >= this_end)
			जारी;
		अगर (this_end > max)
			this_end = max;
		अगर (this_end > max_seen)
			max_seen = this_end;
	पूर्ण

	वापस max_seen - base;
पूर्ण

अटल व्योम jbusmc_स्थिरruct_one_dimm_group(काष्ठा jbusmc *p,
					    अचिन्हित दीर्घ index,
					    स्थिर काष्ठा linux_prom64_रेजिस्टरs *mem_regs,
					    पूर्णांक num_mem_regs)
अणु
	काष्ठा jbusmc_dimm_group *dp = &p->dimm_groups[index];

	dp->controller = p;
	dp->index = index;

	dp->base_addr  = (p->portid * (64UL * 1024 * 1024 * 1024));
	dp->base_addr += (index * (8UL * 1024 * 1024 * 1024));
	dp->size = jbusmc_dimm_group_size(dp->base_addr, mem_regs, num_mem_regs);
पूर्ण

अटल व्योम jbusmc_स्थिरruct_dimm_groups(काष्ठा jbusmc *p,
					 स्थिर काष्ठा linux_prom64_रेजिस्टरs *mem_regs,
					 पूर्णांक num_mem_regs)
अणु
	अगर (p->mc_reg_1 & JB_MC_REG1_DIMM1_BANK0) अणु
		jbusmc_स्थिरruct_one_dimm_group(p, 0, mem_regs, num_mem_regs);
		p->num_dimm_groups++;
	पूर्ण
	अगर (p->mc_reg_1 & JB_MC_REG1_DIMM2_BANK2) अणु
		jbusmc_स्थिरruct_one_dimm_group(p, 1, mem_regs, num_mem_regs);
		p->num_dimm_groups++;
	पूर्ण
पूर्ण

अटल पूर्णांक jbusmc_probe(काष्ठा platक्रमm_device *op)
अणु
	स्थिर काष्ठा linux_prom64_रेजिस्टरs *mem_regs;
	काष्ठा device_node *mem_node;
	पूर्णांक err, len, num_mem_regs;
	काष्ठा jbusmc *p;
	स्थिर u32 *prop;
	स्थिर व्योम *ml;

	err = -ENODEV;
	mem_node = of_find_node_by_path("/memory");
	अगर (!mem_node) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot find /memory node.\n");
		जाओ out;
	पूर्ण
	mem_regs = of_get_property(mem_node, "reg", &len);
	अगर (!mem_regs) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot get reg property of /memory node.\n");
		जाओ out;
	पूर्ण
	num_mem_regs = len / माप(*mem_regs);

	err = -ENOMEM;
	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (!p) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot allocate struct jbusmc.\n");
		जाओ out;
	पूर्ण

	INIT_LIST_HEAD(&p->list);

	err = -ENODEV;
	prop = of_get_property(op->dev.of_node, "portid", &len);
	अगर (!prop || len != 4) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot find portid.\n");
		जाओ out_मुक्त;
	पूर्ण

	p->portid = *prop;

	prop = of_get_property(op->dev.of_node, "memory-control-register-1", &len);
	अगर (!prop || len != 8) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot get memory control register 1.\n");
		जाओ out_मुक्त;
	पूर्ण

	p->mc_reg_1 = ((u64)prop[0] << 32) | (u64) prop[1];

	err = -ENOMEM;
	p->regs = of_ioremap(&op->resource[0], 0, JBUSMC_REGS_SIZE, "jbusmc");
	अगर (!p->regs) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot map jbusmc regs.\n");
		जाओ out_मुक्त;
	पूर्ण

	err = -ENODEV;
	ml = of_get_property(op->dev.of_node, "memory-layout", &p->layout_len);
	अगर (!ml) अणु
		prपूर्णांकk(KERN_ERR PFX "Cannot get memory layout property.\n");
		जाओ out_iounmap;
	पूर्ण
	अगर (p->layout_len > माप(p->layout)) अणु
		prपूर्णांकk(KERN_ERR PFX "Unexpected memory-layout size %d\n",
		       p->layout_len);
		जाओ out_iounmap;
	पूर्ण
	स_नकल(&p->layout, ml, p->layout_len);

	jbusmc_स्थिरruct_dimm_groups(p, mem_regs, num_mem_regs);

	mc_list_add(&p->list);

	prपूर्णांकk(KERN_INFO PFX "UltraSPARC-IIIi memory controller at %pOF\n",
	       op->dev.of_node);

	dev_set_drvdata(&op->dev, p);

	err = 0;

out:
	वापस err;

out_iounmap:
	of_iounmap(&op->resource[0], p->regs, JBUSMC_REGS_SIZE);

out_मुक्त:
	kमुक्त(p);
	जाओ out;
पूर्ण

/* Does BANK decode PHYS_ADDR? */
अटल पूर्णांक chmc_bank_match(काष्ठा chmc_bank_info *bp, अचिन्हित दीर्घ phys_addr)
अणु
	अचिन्हित दीर्घ upper_bits = (phys_addr & PA_UPPER_BITS) >> PA_UPPER_BITS_SHIFT;
	अचिन्हित दीर्घ lower_bits = (phys_addr & PA_LOWER_BITS) >> PA_LOWER_BITS_SHIFT;

	/* Bank must be enabled to match. */
	अगर (bp->valid == 0)
		वापस 0;

	/* Would BANK match upper bits? */
	upper_bits ^= bp->um;		/* What bits are dअगरferent? */
	upper_bits  = ~upper_bits;	/* Invert. */
	upper_bits |= bp->uk;		/* What bits करोn't matter क्रम matching? */
	upper_bits  = ~upper_bits;	/* Invert. */

	अगर (upper_bits)
		वापस 0;

	/* Would BANK match lower bits? */
	lower_bits ^= bp->lm;		/* What bits are dअगरferent? */
	lower_bits  = ~lower_bits;	/* Invert. */
	lower_bits |= bp->lk;		/* What bits करोn't matter क्रम matching? */
	lower_bits  = ~lower_bits;	/* Invert. */

	अगर (lower_bits)
		वापस 0;

	/* I always knew you'd be the one. */
	वापस 1;
पूर्ण

/* Given PHYS_ADDR, search memory controller banks क्रम a match. */
अटल काष्ठा chmc_bank_info *chmc_find_bank(अचिन्हित दीर्घ phys_addr)
अणु
	काष्ठा chmc *p;

	list_क्रम_each_entry(p, &mctrl_list, list) अणु
		पूर्णांक bank_no;

		क्रम (bank_no = 0; bank_no < CHMCTRL_NBANKS; bank_no++) अणु
			काष्ठा chmc_bank_info *bp;

			bp = &p->logical_banks[bank_no];
			अगर (chmc_bank_match(bp, phys_addr))
				वापस bp;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/* This is the मुख्य purpose of this driver. */
अटल पूर्णांक chmc_prपूर्णांक_dimm(पूर्णांक syndrome_code,
			   अचिन्हित दीर्घ phys_addr,
			   अक्षर *buf, पूर्णांक buflen)
अणु
	काष्ठा chmc_bank_info *bp;
	काष्ठा chmc_obp_mem_layout *prop;
	पूर्णांक bank_in_controller, first_dimm;

	bp = chmc_find_bank(phys_addr);
	अगर (bp == शून्य ||
	    syndrome_code < SYNDROME_MIN ||
	    syndrome_code > SYNDROME_MAX) अणु
		buf[0] = '?';
		buf[1] = '?';
		buf[2] = '?';
		buf[3] = '\0';
		वापस 0;
	पूर्ण

	prop = &bp->p->layout_prop;
	bank_in_controller = bp->bank_id & (CHMCTRL_NBANKS - 1);
	first_dimm  = (bank_in_controller & (CHMCTRL_NDGRPS - 1));
	first_dimm *= CHMCTRL_NDIMMS;

	अगर (syndrome_code != SYNDROME_MIN) अणु
		अक्षर *dimm_str;
		पूर्णांक pin;

		get_pin_and_dimm_str(syndrome_code, phys_addr, &pin,
				     &dimm_str, prop, first_dimm);
		प्र_लिखो(buf, "%s, pin %3d", dimm_str, pin);
	पूर्ण अन्यथा अणु
		पूर्णांक dimm;

		/* Multi-bit error, we just dump out all the
		 * dimm labels associated with this bank.
		 */
		क्रम (dimm = 0; dimm < CHMCTRL_NDIMMS; dimm++) अणु
			प्र_लिखो(buf, "%s ",
				prop->dimm_labels[first_dimm + dimm]);
			buf += म_माप(buf);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Accessing the रेजिस्टरs is slightly complicated.  If you want
 * to get at the memory controller which is on the same processor
 * the code is executing, you must use special ASI load/store अन्यथा
 * you go through the global mapping.
 */
अटल u64 chmc_पढ़ो_mcreg(काष्ठा chmc *p, अचिन्हित दीर्घ offset)
अणु
	अचिन्हित दीर्घ ret, this_cpu;

	preempt_disable();

	this_cpu = real_hard_smp_processor_id();

	अगर (p->portid == this_cpu) अणु
		__यंत्र__ __अस्थिर__("ldxa	[%1] %2, %0"
				     : "=r" (ret)
				     : "r" (offset), "i" (ASI_MCU_CTRL_REG));
	पूर्ण अन्यथा अणु
		__यंत्र__ __अस्थिर__("ldxa	[%1] %2, %0"
				     : "=r" (ret)
				     : "r" (p->regs + offset),
				       "i" (ASI_PHYS_BYPASS_EC_E));
	पूर्ण

	preempt_enable();

	वापस ret;
पूर्ण

#अगर 0 /* currently unused */
अटल व्योम chmc_ग_लिखो_mcreg(काष्ठा chmc *p, अचिन्हित दीर्घ offset, u64 val)
अणु
	अगर (p->portid == smp_processor_id()) अणु
		__यंत्र__ __अस्थिर__("stxa	%0, [%1] %2"
				     : : "r" (val),
				         "r" (offset), "i" (ASI_MCU_CTRL_REG));
	पूर्ण अन्यथा अणु
		__यंत्र__ __अस्थिर__("ldxa	%0, [%1] %2"
				     : : "r" (val),
				         "r" (p->regs + offset),
				         "i" (ASI_PHYS_BYPASS_EC_E));
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम chmc_पूर्णांकerpret_one_decode_reg(काष्ठा chmc *p, पूर्णांक which_bank, u64 val)
अणु
	काष्ठा chmc_bank_info *bp = &p->logical_banks[which_bank];

	bp->p = p;
	bp->bank_id = (CHMCTRL_NBANKS * p->portid) + which_bank;
	bp->raw_reg = val;
	bp->valid = (val & MEM_DECODE_VALID) >> MEM_DECODE_VALID_SHIFT;
	bp->uk = (val & MEM_DECODE_UK) >> MEM_DECODE_UK_SHIFT;
	bp->um = (val & MEM_DECODE_UM) >> MEM_DECODE_UM_SHIFT;
	bp->lk = (val & MEM_DECODE_LK) >> MEM_DECODE_LK_SHIFT;
	bp->lm = (val & MEM_DECODE_LM) >> MEM_DECODE_LM_SHIFT;

	bp->base  =  (bp->um);
	bp->base &= ~(bp->uk);
	bp->base <<= PA_UPPER_BITS_SHIFT;

	चयन(bp->lk) अणु
	हाल 0xf:
	शेष:
		bp->पूर्णांकerleave = 1;
		अवरोध;

	हाल 0xe:
		bp->पूर्णांकerleave = 2;
		अवरोध;

	हाल 0xc:
		bp->पूर्णांकerleave = 4;
		अवरोध;

	हाल 0x8:
		bp->पूर्णांकerleave = 8;
		अवरोध;

	हाल 0x0:
		bp->पूर्णांकerleave = 16;
		अवरोध;
	पूर्ण

	/* UK[10] is reserved, and UK[11] is not set क्रम the SDRAM
	 * bank size definition.
	 */
	bp->size = (((अचिन्हित दीर्घ)bp->uk &
		     ((1UL << 10UL) - 1UL)) + 1UL) << PA_UPPER_BITS_SHIFT;
	bp->size /= bp->पूर्णांकerleave;
पूर्ण

अटल व्योम chmc_fetch_decode_regs(काष्ठा chmc *p)
अणु
	अगर (p->layout_size == 0)
		वापस;

	chmc_पूर्णांकerpret_one_decode_reg(p, 0,
				      chmc_पढ़ो_mcreg(p, CHMCTRL_DECODE1));
	chmc_पूर्णांकerpret_one_decode_reg(p, 1,
				      chmc_पढ़ो_mcreg(p, CHMCTRL_DECODE2));
	chmc_पूर्णांकerpret_one_decode_reg(p, 2,
				      chmc_पढ़ो_mcreg(p, CHMCTRL_DECODE3));
	chmc_पूर्णांकerpret_one_decode_reg(p, 3,
				      chmc_पढ़ो_mcreg(p, CHMCTRL_DECODE4));
पूर्ण

अटल पूर्णांक chmc_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *dp = op->dev.of_node;
	अचिन्हित दीर्घ ver;
	स्थिर व्योम *pval;
	पूर्णांक len, portid;
	काष्ठा chmc *p;
	पूर्णांक err;

	err = -ENODEV;
	__यंत्र__ ("rdpr %%ver, %0" : "=r" (ver));
	अगर ((ver >> 32UL) == __JALAPENO_ID ||
	    (ver >> 32UL) == __SERRANO_ID)
		जाओ out;

	portid = of_getपूर्णांकprop_शेष(dp, "portid", -1);
	अगर (portid == -1)
		जाओ out;

	pval = of_get_property(dp, "memory-layout", &len);
	अगर (pval && len > माप(p->layout_prop)) अणु
		prपूर्णांकk(KERN_ERR PFX "Unexpected memory-layout property "
		       "size %d.\n", len);
		जाओ out;
	पूर्ण

	err = -ENOMEM;
	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (!p) अणु
		prपूर्णांकk(KERN_ERR PFX "Could not allocate struct chmc.\n");
		जाओ out;
	पूर्ण

	p->portid = portid;
	p->layout_size = len;
	अगर (!pval)
		p->layout_size = 0;
	अन्यथा
		स_नकल(&p->layout_prop, pval, len);

	p->regs = of_ioremap(&op->resource[0], 0, 0x48, "chmc");
	अगर (!p->regs) अणु
		prपूर्णांकk(KERN_ERR PFX "Could not map registers.\n");
		जाओ out_मुक्त;
	पूर्ण

	अगर (p->layout_size != 0UL) अणु
		p->timing_control1 = chmc_पढ़ो_mcreg(p, CHMCTRL_TCTRL1);
		p->timing_control2 = chmc_पढ़ो_mcreg(p, CHMCTRL_TCTRL2);
		p->timing_control3 = chmc_पढ़ो_mcreg(p, CHMCTRL_TCTRL3);
		p->timing_control4 = chmc_पढ़ो_mcreg(p, CHMCTRL_TCTRL4);
		p->memaddr_control = chmc_पढ़ो_mcreg(p, CHMCTRL_MACTRL);
	पूर्ण

	chmc_fetch_decode_regs(p);

	mc_list_add(&p->list);

	prपूर्णांकk(KERN_INFO PFX "UltraSPARC-III memory controller at %pOF [%s]\n",
	       dp,
	       (p->layout_size ? "ACTIVE" : "INACTIVE"));

	dev_set_drvdata(&op->dev, p);

	err = 0;

out:
	वापस err;

out_मुक्त:
	kमुक्त(p);
	जाओ out;
पूर्ण

अटल पूर्णांक us3mc_probe(काष्ठा platक्रमm_device *op)
अणु
	अगर (mc_type == MC_TYPE_SAFARI)
		वापस chmc_probe(op);
	अन्यथा अगर (mc_type == MC_TYPE_JBUS)
		वापस jbusmc_probe(op);
	वापस -ENODEV;
पूर्ण

अटल व्योम chmc_destroy(काष्ठा platक्रमm_device *op, काष्ठा chmc *p)
अणु
	list_del(&p->list);
	of_iounmap(&op->resource[0], p->regs, 0x48);
	kमुक्त(p);
पूर्ण

अटल व्योम jbusmc_destroy(काष्ठा platक्रमm_device *op, काष्ठा jbusmc *p)
अणु
	mc_list_del(&p->list);
	of_iounmap(&op->resource[0], p->regs, JBUSMC_REGS_SIZE);
	kमुक्त(p);
पूर्ण

अटल पूर्णांक us3mc_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	व्योम *p = dev_get_drvdata(&op->dev);

	अगर (p) अणु
		अगर (mc_type == MC_TYPE_SAFARI)
			chmc_destroy(op, p);
		अन्यथा अगर (mc_type == MC_TYPE_JBUS)
			jbusmc_destroy(op, p);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id us3mc_match[] = अणु
	अणु
		.name = "memory-controller",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, us3mc_match);

अटल काष्ठा platक्रमm_driver us3mc_driver = अणु
	.driver = अणु
		.name = "us3mc",
		.of_match_table = us3mc_match,
	पूर्ण,
	.probe		= us3mc_probe,
	.हटाओ		= us3mc_हटाओ,
पूर्ण;

अटल अंतरभूत bool us3mc_platक्रमm(व्योम)
अणु
	अगर (tlb_type == cheetah || tlb_type == cheetah_plus)
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक __init us3mc_init(व्योम)
अणु
	अचिन्हित दीर्घ ver;
	पूर्णांक ret;

	अगर (!us3mc_platक्रमm())
		वापस -ENODEV;

	__यंत्र__ __अस्थिर__("rdpr %%ver, %0" : "=r" (ver));
	अगर ((ver >> 32UL) == __JALAPENO_ID ||
	    (ver >> 32UL) == __SERRANO_ID) अणु
		mc_type = MC_TYPE_JBUS;
		us3mc_dimm_prपूर्णांकer = jbusmc_prपूर्णांक_dimm;
	पूर्ण अन्यथा अणु
		mc_type = MC_TYPE_SAFARI;
		us3mc_dimm_prपूर्णांकer = chmc_prपूर्णांक_dimm;
	पूर्ण

	ret = रेजिस्टर_dimm_prपूर्णांकer(us3mc_dimm_prपूर्णांकer);

	अगर (!ret) अणु
		ret = platक्रमm_driver_रेजिस्टर(&us3mc_driver);
		अगर (ret)
			unरेजिस्टर_dimm_prपूर्णांकer(us3mc_dimm_prपूर्णांकer);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम __निकास us3mc_cleanup(व्योम)
अणु
	अगर (us3mc_platक्रमm()) अणु
		unरेजिस्टर_dimm_prपूर्णांकer(us3mc_dimm_prपूर्णांकer);
		platक्रमm_driver_unरेजिस्टर(&us3mc_driver);
	पूर्ण
पूर्ण

module_init(us3mc_init);
module_निकास(us3mc_cleanup);
