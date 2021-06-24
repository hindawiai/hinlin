<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Marvell 88E6xxx VLAN [Spanning Tree] Translation Unit (VTU [STU]) support
 *
 * Copyright (c) 2008 Marvell Semiconductor
 * Copyright (c) 2015 CMC Electronics, Inc.
 * Copyright (c) 2017 Savoir-faire Linux, Inc.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>

#समावेश "chip.h"
#समावेश "global1.h"

/* Offset 0x02: VTU FID Register */

अटल पूर्णांक mv88e6xxx_g1_vtu_fid_पढ़ो(काष्ठा mv88e6xxx_chip *chip,
				     काष्ठा mv88e6xxx_vtu_entry *entry)
अणु
	u16 val;
	पूर्णांक err;

	err = mv88e6xxx_g1_पढ़ो(chip, MV88E6352_G1_VTU_FID, &val);
	अगर (err)
		वापस err;

	entry->fid = val & MV88E6352_G1_VTU_FID_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_g1_vtu_fid_ग_लिखो(काष्ठा mv88e6xxx_chip *chip,
				      काष्ठा mv88e6xxx_vtu_entry *entry)
अणु
	u16 val = entry->fid & MV88E6352_G1_VTU_FID_MASK;

	वापस mv88e6xxx_g1_ग_लिखो(chip, MV88E6352_G1_VTU_FID, val);
पूर्ण

/* Offset 0x03: VTU SID Register */

अटल पूर्णांक mv88e6xxx_g1_vtu_sid_पढ़ो(काष्ठा mv88e6xxx_chip *chip,
				     काष्ठा mv88e6xxx_vtu_entry *entry)
अणु
	u16 val;
	पूर्णांक err;

	err = mv88e6xxx_g1_पढ़ो(chip, MV88E6352_G1_VTU_SID, &val);
	अगर (err)
		वापस err;

	entry->sid = val & MV88E6352_G1_VTU_SID_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_g1_vtu_sid_ग_लिखो(काष्ठा mv88e6xxx_chip *chip,
				      काष्ठा mv88e6xxx_vtu_entry *entry)
अणु
	u16 val = entry->sid & MV88E6352_G1_VTU_SID_MASK;

	वापस mv88e6xxx_g1_ग_लिखो(chip, MV88E6352_G1_VTU_SID, val);
पूर्ण

/* Offset 0x05: VTU Operation Register */

अटल पूर्णांक mv88e6xxx_g1_vtu_op_रुको(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक bit = __bf_shf(MV88E6XXX_G1_VTU_OP_BUSY);

	वापस mv88e6xxx_g1_रुको_bit(chip, MV88E6XXX_G1_VTU_OP, bit, 0);
पूर्ण

अटल पूर्णांक mv88e6xxx_g1_vtu_op(काष्ठा mv88e6xxx_chip *chip, u16 op)
अणु
	पूर्णांक err;

	err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_VTU_OP,
				 MV88E6XXX_G1_VTU_OP_BUSY | op);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_g1_vtu_op_रुको(chip);
पूर्ण

/* Offset 0x06: VTU VID Register */

अटल पूर्णांक mv88e6xxx_g1_vtu_vid_पढ़ो(काष्ठा mv88e6xxx_chip *chip,
				     काष्ठा mv88e6xxx_vtu_entry *entry)
अणु
	u16 val;
	पूर्णांक err;

	err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_VTU_VID, &val);
	अगर (err)
		वापस err;

	entry->vid = val & 0xfff;

	अगर (val & MV88E6390_G1_VTU_VID_PAGE)
		entry->vid |= 0x1000;

	entry->valid = !!(val & MV88E6XXX_G1_VTU_VID_VALID);

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_g1_vtu_vid_ग_लिखो(काष्ठा mv88e6xxx_chip *chip,
				      काष्ठा mv88e6xxx_vtu_entry *entry)
अणु
	u16 val = entry->vid & 0xfff;

	अगर (entry->vid & 0x1000)
		val |= MV88E6390_G1_VTU_VID_PAGE;

	अगर (entry->valid)
		val |= MV88E6XXX_G1_VTU_VID_VALID;

	वापस mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_VTU_VID, val);
पूर्ण

/* Offset 0x07: VTU/STU Data Register 1
 * Offset 0x08: VTU/STU Data Register 2
 * Offset 0x09: VTU/STU Data Register 3
 */
अटल पूर्णांक mv88e6185_g1_vtu_stu_data_पढ़ो(काष्ठा mv88e6xxx_chip *chip,
					  u16 *regs)
अणु
	पूर्णांक i;

	/* Read all 3 VTU/STU Data रेजिस्टरs */
	क्रम (i = 0; i < 3; ++i) अणु
		u16 *reg = &regs[i];
		पूर्णांक err;

		err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_VTU_DATA1 + i, reg);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6185_g1_vtu_data_पढ़ो(काष्ठा mv88e6xxx_chip *chip,
				      काष्ठा mv88e6xxx_vtu_entry *entry)
अणु
	u16 regs[3];
	पूर्णांक err;
	पूर्णांक i;

	err = mv88e6185_g1_vtu_stu_data_पढ़ो(chip, regs);
	अगर (err)
		वापस err;

	/* Extract MemberTag data */
	क्रम (i = 0; i < mv88e6xxx_num_ports(chip); ++i) अणु
		अचिन्हित पूर्णांक member_offset = (i % 4) * 4;

		entry->member[i] = (regs[i / 4] >> member_offset) & 0x3;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6185_g1_stu_data_पढ़ो(काष्ठा mv88e6xxx_chip *chip,
				      काष्ठा mv88e6xxx_vtu_entry *entry)
अणु
	u16 regs[3];
	पूर्णांक err;
	पूर्णांक i;

	err = mv88e6185_g1_vtu_stu_data_पढ़ो(chip, regs);
	अगर (err)
		वापस err;

	/* Extract PortState data */
	क्रम (i = 0; i < mv88e6xxx_num_ports(chip); ++i) अणु
		अचिन्हित पूर्णांक state_offset = (i % 4) * 4 + 2;

		entry->state[i] = (regs[i / 4] >> state_offset) & 0x3;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6185_g1_vtu_data_ग_लिखो(काष्ठा mv88e6xxx_chip *chip,
				       काष्ठा mv88e6xxx_vtu_entry *entry)
अणु
	u16 regs[3] = अणु 0 पूर्ण;
	पूर्णांक i;

	/* Insert MemberTag and PortState data */
	क्रम (i = 0; i < mv88e6xxx_num_ports(chip); ++i) अणु
		अचिन्हित पूर्णांक member_offset = (i % 4) * 4;
		अचिन्हित पूर्णांक state_offset = member_offset + 2;

		regs[i / 4] |= (entry->member[i] & 0x3) << member_offset;
		regs[i / 4] |= (entry->state[i] & 0x3) << state_offset;
	पूर्ण

	/* Write all 3 VTU/STU Data रेजिस्टरs */
	क्रम (i = 0; i < 3; ++i) अणु
		u16 reg = regs[i];
		पूर्णांक err;

		err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_VTU_DATA1 + i, reg);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6390_g1_vtu_data_पढ़ो(काष्ठा mv88e6xxx_chip *chip, u8 *data)
अणु
	u16 regs[2];
	पूर्णांक i;

	/* Read the 2 VTU/STU Data रेजिस्टरs */
	क्रम (i = 0; i < 2; ++i) अणु
		u16 *reg = &regs[i];
		पूर्णांक err;

		err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_VTU_DATA1 + i, reg);
		अगर (err)
			वापस err;
	पूर्ण

	/* Extract data */
	क्रम (i = 0; i < mv88e6xxx_num_ports(chip); ++i) अणु
		अचिन्हित पूर्णांक offset = (i % 8) * 2;

		data[i] = (regs[i / 8] >> offset) & 0x3;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6390_g1_vtu_data_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, u8 *data)
अणु
	u16 regs[2] = अणु 0 पूर्ण;
	पूर्णांक i;

	/* Insert data */
	क्रम (i = 0; i < mv88e6xxx_num_ports(chip); ++i) अणु
		अचिन्हित पूर्णांक offset = (i % 8) * 2;

		regs[i / 8] |= (data[i] & 0x3) << offset;
	पूर्ण

	/* Write the 2 VTU/STU Data रेजिस्टरs */
	क्रम (i = 0; i < 2; ++i) अणु
		u16 reg = regs[i];
		पूर्णांक err;

		err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_VTU_DATA1 + i, reg);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* VLAN Translation Unit Operations */

अटल पूर्णांक mv88e6xxx_g1_vtu_stu_getnext(काष्ठा mv88e6xxx_chip *chip,
					काष्ठा mv88e6xxx_vtu_entry *entry)
अणु
	पूर्णांक err;

	err = mv88e6xxx_g1_vtu_sid_ग_लिखो(chip, entry);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g1_vtu_op(chip, MV88E6XXX_G1_VTU_OP_STU_GET_NEXT);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g1_vtu_sid_पढ़ो(chip, entry);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_g1_vtu_vid_पढ़ो(chip, entry);
पूर्ण

अटल पूर्णांक mv88e6xxx_g1_vtu_stu_get(काष्ठा mv88e6xxx_chip *chip,
				    काष्ठा mv88e6xxx_vtu_entry *vtu)
अणु
	काष्ठा mv88e6xxx_vtu_entry stu;
	पूर्णांक err;

	err = mv88e6xxx_g1_vtu_sid_पढ़ो(chip, vtu);
	अगर (err)
		वापस err;

	stu.sid = vtu->sid - 1;

	err = mv88e6xxx_g1_vtu_stu_getnext(chip, &stu);
	अगर (err)
		वापस err;

	अगर (stu.sid != vtu->sid || !stu.valid)
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक mv88e6xxx_g1_vtu_getnext(काष्ठा mv88e6xxx_chip *chip,
			     काष्ठा mv88e6xxx_vtu_entry *entry)
अणु
	पूर्णांक err;

	err = mv88e6xxx_g1_vtu_op_रुको(chip);
	अगर (err)
		वापस err;

	/* To get the next higher active VID, the VTU GetNext operation can be
	 * started again without setting the VID रेजिस्टरs since it alपढ़ोy
	 * contains the last VID.
	 *
	 * To save a few hardware accesses and असलtract this to the caller,
	 * ग_लिखो the VID only once, when the entry is given as invalid.
	 */
	अगर (!entry->valid) अणु
		err = mv88e6xxx_g1_vtu_vid_ग_लिखो(chip, entry);
		अगर (err)
			वापस err;
	पूर्ण

	err = mv88e6xxx_g1_vtu_op(chip, MV88E6XXX_G1_VTU_OP_VTU_GET_NEXT);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_g1_vtu_vid_पढ़ो(chip, entry);
पूर्ण

पूर्णांक mv88e6185_g1_vtu_getnext(काष्ठा mv88e6xxx_chip *chip,
			     काष्ठा mv88e6xxx_vtu_entry *entry)
अणु
	u16 val;
	पूर्णांक err;

	err = mv88e6xxx_g1_vtu_getnext(chip, entry);
	अगर (err)
		वापस err;

	अगर (entry->valid) अणु
		err = mv88e6185_g1_vtu_data_पढ़ो(chip, entry);
		अगर (err)
			वापस err;

		err = mv88e6185_g1_stu_data_पढ़ो(chip, entry);
		अगर (err)
			वापस err;

		/* VTU DBNum[3:0] are located in VTU Operation 3:0
		 * VTU DBNum[7:4] ([5:4] क्रम 6250) are located in VTU Operation 11:8 (9:8)
		 */
		err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_VTU_OP, &val);
		अगर (err)
			वापस err;

		entry->fid = val & 0x000f;
		entry->fid |= (val & 0x0f00) >> 4;
		entry->fid &= mv88e6xxx_num_databases(chip) - 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mv88e6352_g1_vtu_getnext(काष्ठा mv88e6xxx_chip *chip,
			     काष्ठा mv88e6xxx_vtu_entry *entry)
अणु
	पूर्णांक err;

	/* Fetch VLAN MemberTag data from the VTU */
	err = mv88e6xxx_g1_vtu_getnext(chip, entry);
	अगर (err)
		वापस err;

	अगर (entry->valid) अणु
		err = mv88e6185_g1_vtu_data_पढ़ो(chip, entry);
		अगर (err)
			वापस err;

		err = mv88e6xxx_g1_vtu_fid_पढ़ो(chip, entry);
		अगर (err)
			वापस err;

		/* Fetch VLAN PortState data from the STU */
		err = mv88e6xxx_g1_vtu_stu_get(chip, entry);
		अगर (err)
			वापस err;

		err = mv88e6185_g1_stu_data_पढ़ो(chip, entry);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mv88e6390_g1_vtu_getnext(काष्ठा mv88e6xxx_chip *chip,
			     काष्ठा mv88e6xxx_vtu_entry *entry)
अणु
	पूर्णांक err;

	/* Fetch VLAN MemberTag data from the VTU */
	err = mv88e6xxx_g1_vtu_getnext(chip, entry);
	अगर (err)
		वापस err;

	अगर (entry->valid) अणु
		err = mv88e6390_g1_vtu_data_पढ़ो(chip, entry->member);
		अगर (err)
			वापस err;

		/* Fetch VLAN PortState data from the STU */
		err = mv88e6xxx_g1_vtu_stu_get(chip, entry);
		अगर (err)
			वापस err;

		err = mv88e6390_g1_vtu_data_पढ़ो(chip, entry->state);
		अगर (err)
			वापस err;

		err = mv88e6xxx_g1_vtu_fid_पढ़ो(chip, entry);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mv88e6185_g1_vtu_loadpurge(काष्ठा mv88e6xxx_chip *chip,
			       काष्ठा mv88e6xxx_vtu_entry *entry)
अणु
	u16 op = MV88E6XXX_G1_VTU_OP_VTU_LOAD_PURGE;
	पूर्णांक err;

	err = mv88e6xxx_g1_vtu_op_रुको(chip);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g1_vtu_vid_ग_लिखो(chip, entry);
	अगर (err)
		वापस err;

	अगर (entry->valid) अणु
		err = mv88e6185_g1_vtu_data_ग_लिखो(chip, entry);
		अगर (err)
			वापस err;

		/* VTU DBNum[3:0] are located in VTU Operation 3:0
		 * VTU DBNum[7:4] are located in VTU Operation 11:8
		 *
		 * For the 6250/6220, the latter are really [5:4] and
		 * 9:8, but in those हालs bits 7:6 of entry->fid are
		 * 0 since they have num_databases = 64.
		 */
		op |= entry->fid & 0x000f;
		op |= (entry->fid & 0x00f0) << 4;
	पूर्ण

	वापस mv88e6xxx_g1_vtu_op(chip, op);
पूर्ण

पूर्णांक mv88e6352_g1_vtu_loadpurge(काष्ठा mv88e6xxx_chip *chip,
			       काष्ठा mv88e6xxx_vtu_entry *entry)
अणु
	पूर्णांक err;

	err = mv88e6xxx_g1_vtu_op_रुको(chip);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g1_vtu_vid_ग_लिखो(chip, entry);
	अगर (err)
		वापस err;

	अगर (entry->valid) अणु
		/* Write MemberTag and PortState data */
		err = mv88e6185_g1_vtu_data_ग_लिखो(chip, entry);
		अगर (err)
			वापस err;

		err = mv88e6xxx_g1_vtu_sid_ग_लिखो(chip, entry);
		अगर (err)
			वापस err;

		/* Load STU entry */
		err = mv88e6xxx_g1_vtu_op(chip,
					  MV88E6XXX_G1_VTU_OP_STU_LOAD_PURGE);
		अगर (err)
			वापस err;

		err = mv88e6xxx_g1_vtu_fid_ग_लिखो(chip, entry);
		अगर (err)
			वापस err;
	पूर्ण

	/* Load/Purge VTU entry */
	वापस mv88e6xxx_g1_vtu_op(chip, MV88E6XXX_G1_VTU_OP_VTU_LOAD_PURGE);
पूर्ण

पूर्णांक mv88e6390_g1_vtu_loadpurge(काष्ठा mv88e6xxx_chip *chip,
			       काष्ठा mv88e6xxx_vtu_entry *entry)
अणु
	पूर्णांक err;

	err = mv88e6xxx_g1_vtu_op_रुको(chip);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g1_vtu_vid_ग_लिखो(chip, entry);
	अगर (err)
		वापस err;

	अगर (entry->valid) अणु
		/* Write PortState data */
		err = mv88e6390_g1_vtu_data_ग_लिखो(chip, entry->state);
		अगर (err)
			वापस err;

		err = mv88e6xxx_g1_vtu_sid_ग_लिखो(chip, entry);
		अगर (err)
			वापस err;

		/* Load STU entry */
		err = mv88e6xxx_g1_vtu_op(chip,
					  MV88E6XXX_G1_VTU_OP_STU_LOAD_PURGE);
		अगर (err)
			वापस err;

		/* Write MemberTag data */
		err = mv88e6390_g1_vtu_data_ग_लिखो(chip, entry->member);
		अगर (err)
			वापस err;

		err = mv88e6xxx_g1_vtu_fid_ग_लिखो(chip, entry);
		अगर (err)
			वापस err;
	पूर्ण

	/* Load/Purge VTU entry */
	वापस mv88e6xxx_g1_vtu_op(chip, MV88E6XXX_G1_VTU_OP_VTU_LOAD_PURGE);
पूर्ण

पूर्णांक mv88e6xxx_g1_vtu_flush(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक err;

	err = mv88e6xxx_g1_vtu_op_रुको(chip);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_g1_vtu_op(chip, MV88E6XXX_G1_VTU_OP_FLUSH_ALL);
पूर्ण

अटल irqवापस_t mv88e6xxx_g1_vtu_prob_irq_thपढ़ो_fn(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mv88e6xxx_chip *chip = dev_id;
	काष्ठा mv88e6xxx_vtu_entry entry;
	पूर्णांक spid;
	पूर्णांक err;
	u16 val;

	mv88e6xxx_reg_lock(chip);

	err = mv88e6xxx_g1_vtu_op(chip, MV88E6XXX_G1_VTU_OP_GET_CLR_VIOLATION);
	अगर (err)
		जाओ out;

	err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_VTU_OP, &val);
	अगर (err)
		जाओ out;

	err = mv88e6xxx_g1_vtu_vid_पढ़ो(chip, &entry);
	अगर (err)
		जाओ out;

	spid = val & MV88E6XXX_G1_VTU_OP_SPID_MASK;

	अगर (val & MV88E6XXX_G1_VTU_OP_MEMBER_VIOLATION) अणु
		dev_err_ratelimited(chip->dev, "VTU member violation for vid %d, source port %d\n",
				    entry.vid, spid);
		chip->ports[spid].vtu_member_violation++;
	पूर्ण

	अगर (val & MV88E6XXX_G1_VTU_OP_MISS_VIOLATION) अणु
		dev_dbg_ratelimited(chip->dev, "VTU miss violation for vid %d, source port %d\n",
				    entry.vid, spid);
		chip->ports[spid].vtu_miss_violation++;
	पूर्ण

	mv88e6xxx_reg_unlock(chip);

	वापस IRQ_HANDLED;

out:
	mv88e6xxx_reg_unlock(chip);

	dev_err(chip->dev, "VTU problem: error %d while handling interrupt\n",
		err);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक mv88e6xxx_g1_vtu_prob_irq_setup(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक err;

	chip->vtu_prob_irq = irq_find_mapping(chip->g1_irq.करोमुख्य,
					      MV88E6XXX_G1_STS_IRQ_VTU_PROB);
	अगर (chip->vtu_prob_irq < 0)
		वापस chip->vtu_prob_irq;

	snम_लिखो(chip->vtu_prob_irq_name, माप(chip->vtu_prob_irq_name),
		 "mv88e6xxx-%s-g1-vtu-prob", dev_name(chip->dev));

	err = request_thपढ़ोed_irq(chip->vtu_prob_irq, शून्य,
				   mv88e6xxx_g1_vtu_prob_irq_thपढ़ो_fn,
				   IRQF_ONESHOT, chip->vtu_prob_irq_name,
				   chip);
	अगर (err)
		irq_dispose_mapping(chip->vtu_prob_irq);

	वापस err;
पूर्ण

व्योम mv88e6xxx_g1_vtu_prob_irq_मुक्त(काष्ठा mv88e6xxx_chip *chip)
अणु
	मुक्त_irq(chip->vtu_prob_irq, chip);
	irq_dispose_mapping(chip->vtu_prob_irq);
पूर्ण
