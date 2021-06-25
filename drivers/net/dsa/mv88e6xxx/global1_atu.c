<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Marvell 88E6xxx Address Translation Unit (ATU) support
 *
 * Copyright (c) 2008 Marvell Semiconductor
 * Copyright (c) 2017 Savoir-faire Linux, Inc.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>

#समावेश "chip.h"
#समावेश "global1.h"

/* Offset 0x01: ATU FID Register */

अटल पूर्णांक mv88e6xxx_g1_atu_fid_ग_लिखो(काष्ठा mv88e6xxx_chip *chip, u16 fid)
अणु
	वापस mv88e6xxx_g1_ग_लिखो(chip, MV88E6352_G1_ATU_FID, fid & 0xfff);
पूर्ण

/* Offset 0x0A: ATU Control Register */

पूर्णांक mv88e6xxx_g1_atu_set_learn2all(काष्ठा mv88e6xxx_chip *chip, bool learn2all)
अणु
	u16 val;
	पूर्णांक err;

	err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_ATU_CTL, &val);
	अगर (err)
		वापस err;

	अगर (learn2all)
		val |= MV88E6XXX_G1_ATU_CTL_LEARN2ALL;
	अन्यथा
		val &= ~MV88E6XXX_G1_ATU_CTL_LEARN2ALL;

	वापस mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_ATU_CTL, val);
पूर्ण

पूर्णांक mv88e6xxx_g1_atu_set_age_समय(काष्ठा mv88e6xxx_chip *chip,
				  अचिन्हित पूर्णांक msecs)
अणु
	स्थिर अचिन्हित पूर्णांक coeff = chip->info->age_समय_coeff;
	स्थिर अचिन्हित पूर्णांक min = 0x01 * coeff;
	स्थिर अचिन्हित पूर्णांक max = 0xff * coeff;
	u8 age_समय;
	u16 val;
	पूर्णांक err;

	अगर (msecs < min || msecs > max)
		वापस -दुस्फल;

	/* Round to nearest multiple of coeff */
	age_समय = (msecs + coeff / 2) / coeff;

	err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_ATU_CTL, &val);
	अगर (err)
		वापस err;

	/* AgeTime is 11:4 bits */
	val &= ~0xff0;
	val |= age_समय << 4;

	err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_ATU_CTL, val);
	अगर (err)
		वापस err;

	dev_dbg(chip->dev, "AgeTime set to 0x%02x (%d ms)\n", age_समय,
		age_समय * coeff);

	वापस 0;
पूर्ण

पूर्णांक mv88e6165_g1_atu_get_hash(काष्ठा mv88e6xxx_chip *chip, u8 *hash)
अणु
	पूर्णांक err;
	u16 val;

	err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_ATU_CTL, &val);
	अगर (err)
		वापस err;

	*hash = val & MV88E6161_G1_ATU_CTL_HASH_MASK;

	वापस 0;
पूर्ण

पूर्णांक mv88e6165_g1_atu_set_hash(काष्ठा mv88e6xxx_chip *chip, u8 hash)
अणु
	पूर्णांक err;
	u16 val;

	अगर (hash & ~MV88E6161_G1_ATU_CTL_HASH_MASK)
		वापस -EINVAL;

	err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_ATU_CTL, &val);
	अगर (err)
		वापस err;

	val &= ~MV88E6161_G1_ATU_CTL_HASH_MASK;
	val |= hash;

	वापस mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_ATU_CTL, val);
पूर्ण

/* Offset 0x0B: ATU Operation Register */

अटल पूर्णांक mv88e6xxx_g1_atu_op_रुको(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक bit = __bf_shf(MV88E6XXX_G1_ATU_OP_BUSY);

	वापस mv88e6xxx_g1_रुको_bit(chip, MV88E6XXX_G1_ATU_OP, bit, 0);
पूर्ण

अटल पूर्णांक mv88e6xxx_g1_atu_op(काष्ठा mv88e6xxx_chip *chip, u16 fid, u16 op)
अणु
	u16 val;
	पूर्णांक err;

	/* FID bits are dispatched all around gradually as more are supported */
	अगर (mv88e6xxx_num_databases(chip) > 256) अणु
		err = mv88e6xxx_g1_atu_fid_ग_लिखो(chip, fid);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		अगर (mv88e6xxx_num_databases(chip) > 64) अणु
			/* ATU DBNum[7:4] are located in ATU Control 15:12 */
			err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_ATU_CTL,
						&val);
			अगर (err)
				वापस err;

			val = (val & 0x0fff) | ((fid << 8) & 0xf000);
			err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_ATU_CTL,
						 val);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अगर (mv88e6xxx_num_databases(chip) > 16) अणु
			/* ATU DBNum[5:4] are located in ATU Operation 9:8 */
			op |= (fid & 0x30) << 4;
		पूर्ण

		/* ATU DBNum[3:0] are located in ATU Operation 3:0 */
		op |= fid & 0xf;
	पूर्ण

	err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_ATU_OP,
				 MV88E6XXX_G1_ATU_OP_BUSY | op);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_g1_atu_op_रुको(chip);
पूर्ण

पूर्णांक mv88e6xxx_g1_atu_get_next(काष्ठा mv88e6xxx_chip *chip, u16 fid)
अणु
	वापस mv88e6xxx_g1_atu_op(chip, fid, MV88E6XXX_G1_ATU_OP_GET_NEXT_DB);
पूर्ण

/* Offset 0x0C: ATU Data Register */

अटल पूर्णांक mv88e6xxx_g1_atu_data_पढ़ो(काष्ठा mv88e6xxx_chip *chip,
				      काष्ठा mv88e6xxx_atu_entry *entry)
अणु
	u16 val;
	पूर्णांक err;

	err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_ATU_DATA, &val);
	अगर (err)
		वापस err;

	entry->state = val & 0xf;
	अगर (entry->state) अणु
		entry->trunk = !!(val & MV88E6XXX_G1_ATU_DATA_TRUNK);
		entry->portvec = (val >> 4) & mv88e6xxx_port_mask(chip);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_g1_atu_data_ग_लिखो(काष्ठा mv88e6xxx_chip *chip,
				       काष्ठा mv88e6xxx_atu_entry *entry)
अणु
	u16 data = entry->state & 0xf;

	अगर (entry->state) अणु
		अगर (entry->trunk)
			data |= MV88E6XXX_G1_ATU_DATA_TRUNK;

		data |= (entry->portvec & mv88e6xxx_port_mask(chip)) << 4;
	पूर्ण

	वापस mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_ATU_DATA, data);
पूर्ण

/* Offset 0x0D: ATU MAC Address Register Bytes 0 & 1
 * Offset 0x0E: ATU MAC Address Register Bytes 2 & 3
 * Offset 0x0F: ATU MAC Address Register Bytes 4 & 5
 */

अटल पूर्णांक mv88e6xxx_g1_atu_mac_पढ़ो(काष्ठा mv88e6xxx_chip *chip,
				     काष्ठा mv88e6xxx_atu_entry *entry)
अणु
	u16 val;
	पूर्णांक i, err;

	क्रम (i = 0; i < 3; i++) अणु
		err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_ATU_MAC01 + i, &val);
		अगर (err)
			वापस err;

		entry->mac[i * 2] = val >> 8;
		entry->mac[i * 2 + 1] = val & 0xff;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mv88e6xxx_g1_atu_mac_ग_लिखो(काष्ठा mv88e6xxx_chip *chip,
				      काष्ठा mv88e6xxx_atu_entry *entry)
अणु
	u16 val;
	पूर्णांक i, err;

	क्रम (i = 0; i < 3; i++) अणु
		val = (entry->mac[i * 2] << 8) | entry->mac[i * 2 + 1];
		err = mv88e6xxx_g1_ग_लिखो(chip, MV88E6XXX_G1_ATU_MAC01 + i, val);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* Address Translation Unit operations */

पूर्णांक mv88e6xxx_g1_atu_getnext(काष्ठा mv88e6xxx_chip *chip, u16 fid,
			     काष्ठा mv88e6xxx_atu_entry *entry)
अणु
	पूर्णांक err;

	err = mv88e6xxx_g1_atu_op_रुको(chip);
	अगर (err)
		वापस err;

	/* Write the MAC address to iterate from only once */
	अगर (!entry->state) अणु
		err = mv88e6xxx_g1_atu_mac_ग_लिखो(chip, entry);
		अगर (err)
			वापस err;
	पूर्ण

	err = mv88e6xxx_g1_atu_op(chip, fid, MV88E6XXX_G1_ATU_OP_GET_NEXT_DB);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g1_atu_data_पढ़ो(chip, entry);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_g1_atu_mac_पढ़ो(chip, entry);
पूर्ण

पूर्णांक mv88e6xxx_g1_atu_loadpurge(काष्ठा mv88e6xxx_chip *chip, u16 fid,
			       काष्ठा mv88e6xxx_atu_entry *entry)
अणु
	पूर्णांक err;

	err = mv88e6xxx_g1_atu_op_रुको(chip);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g1_atu_mac_ग_लिखो(chip, entry);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g1_atu_data_ग_लिखो(chip, entry);
	अगर (err)
		वापस err;

	वापस mv88e6xxx_g1_atu_op(chip, fid, MV88E6XXX_G1_ATU_OP_LOAD_DB);
पूर्ण

अटल पूर्णांक mv88e6xxx_g1_atu_flushmove(काष्ठा mv88e6xxx_chip *chip, u16 fid,
				      काष्ठा mv88e6xxx_atu_entry *entry,
				      bool all)
अणु
	u16 op;
	पूर्णांक err;

	err = mv88e6xxx_g1_atu_op_रुको(chip);
	अगर (err)
		वापस err;

	err = mv88e6xxx_g1_atu_data_ग_लिखो(chip, entry);
	अगर (err)
		वापस err;

	/* Flush/Move all or non-अटल entries from all or a given database */
	अगर (all && fid)
		op = MV88E6XXX_G1_ATU_OP_FLUSH_MOVE_ALL_DB;
	अन्यथा अगर (fid)
		op = MV88E6XXX_G1_ATU_OP_FLUSH_MOVE_NON_STATIC_DB;
	अन्यथा अगर (all)
		op = MV88E6XXX_G1_ATU_OP_FLUSH_MOVE_ALL;
	अन्यथा
		op = MV88E6XXX_G1_ATU_OP_FLUSH_MOVE_NON_STATIC;

	वापस mv88e6xxx_g1_atu_op(chip, fid, op);
पूर्ण

पूर्णांक mv88e6xxx_g1_atu_flush(काष्ठा mv88e6xxx_chip *chip, u16 fid, bool all)
अणु
	काष्ठा mv88e6xxx_atu_entry entry = अणु
		.state = 0, /* Null EntryState means Flush */
	पूर्ण;

	वापस mv88e6xxx_g1_atu_flushmove(chip, fid, &entry, all);
पूर्ण

अटल पूर्णांक mv88e6xxx_g1_atu_move(काष्ठा mv88e6xxx_chip *chip, u16 fid,
				 पूर्णांक from_port, पूर्णांक to_port, bool all)
अणु
	काष्ठा mv88e6xxx_atu_entry entry = अणु 0 पूर्ण;
	अचिन्हित दीर्घ mask;
	पूर्णांक shअगरt;

	अगर (!chip->info->atu_move_port_mask)
		वापस -EOPNOTSUPP;

	mask = chip->info->atu_move_port_mask;
	shअगरt = biपंचांगap_weight(&mask, 16);

	entry.state = 0xf; /* Full EntryState means Move */
	entry.portvec = from_port & mask;
	entry.portvec |= (to_port & mask) << shअगरt;

	वापस mv88e6xxx_g1_atu_flushmove(chip, fid, &entry, all);
पूर्ण

पूर्णांक mv88e6xxx_g1_atu_हटाओ(काष्ठा mv88e6xxx_chip *chip, u16 fid, पूर्णांक port,
			    bool all)
अणु
	पूर्णांक from_port = port;
	पूर्णांक to_port = chip->info->atu_move_port_mask;

	वापस mv88e6xxx_g1_atu_move(chip, fid, from_port, to_port, all);
पूर्ण

अटल irqवापस_t mv88e6xxx_g1_atu_prob_irq_thपढ़ो_fn(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mv88e6xxx_chip *chip = dev_id;
	काष्ठा mv88e6xxx_atu_entry entry;
	पूर्णांक spid;
	पूर्णांक err;
	u16 val;

	mv88e6xxx_reg_lock(chip);

	err = mv88e6xxx_g1_atu_op(chip, 0,
				  MV88E6XXX_G1_ATU_OP_GET_CLR_VIOLATION);
	अगर (err)
		जाओ out;

	err = mv88e6xxx_g1_पढ़ो(chip, MV88E6XXX_G1_ATU_OP, &val);
	अगर (err)
		जाओ out;

	err = mv88e6xxx_g1_atu_data_पढ़ो(chip, &entry);
	अगर (err)
		जाओ out;

	err = mv88e6xxx_g1_atu_mac_पढ़ो(chip, &entry);
	अगर (err)
		जाओ out;

	spid = entry.state;

	अगर (val & MV88E6XXX_G1_ATU_OP_AGE_OUT_VIOLATION) अणु
		dev_err_ratelimited(chip->dev,
				    "ATU age out violation for %pM\n",
				    entry.mac);
	पूर्ण

	अगर (val & MV88E6XXX_G1_ATU_OP_MEMBER_VIOLATION) अणु
		dev_err_ratelimited(chip->dev,
				    "ATU member violation for %pM portvec %x spid %d\n",
				    entry.mac, entry.portvec, spid);
		chip->ports[spid].atu_member_violation++;
	पूर्ण

	अगर (val & MV88E6XXX_G1_ATU_OP_MISS_VIOLATION) अणु
		dev_err_ratelimited(chip->dev,
				    "ATU miss violation for %pM portvec %x spid %d\n",
				    entry.mac, entry.portvec, spid);
		chip->ports[spid].atu_miss_violation++;
	पूर्ण

	अगर (val & MV88E6XXX_G1_ATU_OP_FULL_VIOLATION) अणु
		dev_err_ratelimited(chip->dev,
				    "ATU full violation for %pM portvec %x spid %d\n",
				    entry.mac, entry.portvec, spid);
		chip->ports[spid].atu_full_violation++;
	पूर्ण
	mv88e6xxx_reg_unlock(chip);

	वापस IRQ_HANDLED;

out:
	mv88e6xxx_reg_unlock(chip);

	dev_err(chip->dev, "ATU problem: error %d while handling interrupt\n",
		err);
	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक mv88e6xxx_g1_atu_prob_irq_setup(काष्ठा mv88e6xxx_chip *chip)
अणु
	पूर्णांक err;

	chip->atu_prob_irq = irq_find_mapping(chip->g1_irq.करोमुख्य,
					      MV88E6XXX_G1_STS_IRQ_ATU_PROB);
	अगर (chip->atu_prob_irq < 0)
		वापस chip->atu_prob_irq;

	snम_लिखो(chip->atu_prob_irq_name, माप(chip->atu_prob_irq_name),
		 "mv88e6xxx-%s-g1-atu-prob", dev_name(chip->dev));

	err = request_thपढ़ोed_irq(chip->atu_prob_irq, शून्य,
				   mv88e6xxx_g1_atu_prob_irq_thपढ़ो_fn,
				   IRQF_ONESHOT, chip->atu_prob_irq_name,
				   chip);
	अगर (err)
		irq_dispose_mapping(chip->atu_prob_irq);

	वापस err;
पूर्ण

व्योम mv88e6xxx_g1_atu_prob_irq_मुक्त(काष्ठा mv88e6xxx_chip *chip)
अणु
	मुक्त_irq(chip->atu_prob_irq, chip);
	irq_dispose_mapping(chip->atu_prob_irq);
पूर्ण
