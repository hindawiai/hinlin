<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 */
#समावेश "mt76.h"

अटल पूर्णांक
mt76_reg_set(व्योम *data, u64 val)
अणु
	काष्ठा mt76_dev *dev = data;

	__mt76_wr(dev, dev->debugfs_reg, val);
	वापस 0;
पूर्ण

अटल पूर्णांक
mt76_reg_get(व्योम *data, u64 *val)
अणु
	काष्ठा mt76_dev *dev = data;

	*val = __mt76_rr(dev, dev->debugfs_reg);
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_regval, mt76_reg_get, mt76_reg_set,
			 "0x%08llx\n");

अटल पूर्णांक
mt76_napi_thपढ़ोed_set(व्योम *data, u64 val)
अणु
	काष्ठा mt76_dev *dev = data;

	अगर (!mt76_is_mmio(dev))
		वापस -EOPNOTSUPP;

	अगर (dev->napi_dev.thपढ़ोed != val)
		वापस dev_set_thपढ़ोed(&dev->napi_dev, val);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt76_napi_thपढ़ोed_get(व्योम *data, u64 *val)
अणु
	काष्ठा mt76_dev *dev = data;

	*val = dev->napi_dev.thपढ़ोed;
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_napi_thपढ़ोed, mt76_napi_thपढ़ोed_get,
			 mt76_napi_thपढ़ोed_set, "%llu\n");

पूर्णांक mt76_queues_पढ़ो(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा mt76_dev *dev = dev_get_drvdata(s->निजी);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dev->phy.q_tx); i++) अणु
		काष्ठा mt76_queue *q = dev->phy.q_tx[i];

		अगर (!q)
			जारी;

		seq_म_लिखो(s,
			   "%d:	queued=%d head=%d tail=%d\n",
			   i, q->queued, q->head, q->tail);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_queues_पढ़ो);

अटल पूर्णांक mt76_rx_queues_पढ़ो(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा mt76_dev *dev = dev_get_drvdata(s->निजी);
	पूर्णांक i, queued;

	mt76_क्रम_each_q_rx(dev, i) अणु
		काष्ठा mt76_queue *q = &dev->q_rx[i];

		queued = mt76_is_usb(dev) ? q->ndesc - q->queued : q->queued;
		seq_म_लिखो(s, "%d:	queued=%d head=%d tail=%d\n",
			   i, queued, q->head, q->tail);
	पूर्ण

	वापस 0;
पूर्ण

व्योम mt76_seq_माला_दो_array(काष्ठा seq_file *file, स्थिर अक्षर *str,
			 s8 *val, पूर्णांक len)
अणु
	पूर्णांक i;

	seq_म_लिखो(file, "%10s:", str);
	क्रम (i = 0; i < len; i++)
		seq_म_लिखो(file, " %2d", val[i]);
	seq_माला_दो(file, "\n");
पूर्ण
EXPORT_SYMBOL_GPL(mt76_seq_माला_दो_array);

अटल पूर्णांक mt76_पढ़ो_rate_txघातer(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा mt76_dev *dev = dev_get_drvdata(s->निजी);

	mt76_seq_माला_दो_array(s, "CCK", dev->rate_घातer.cck,
			    ARRAY_SIZE(dev->rate_घातer.cck));
	mt76_seq_माला_दो_array(s, "OFDM", dev->rate_घातer.ofdm,
			    ARRAY_SIZE(dev->rate_घातer.ofdm));
	mt76_seq_माला_दो_array(s, "STBC", dev->rate_घातer.stbc,
			    ARRAY_SIZE(dev->rate_घातer.stbc));
	mt76_seq_माला_दो_array(s, "HT", dev->rate_घातer.ht,
			    ARRAY_SIZE(dev->rate_घातer.ht));
	mt76_seq_माला_दो_array(s, "VHT", dev->rate_घातer.vht,
			    ARRAY_SIZE(dev->rate_घातer.vht));
	वापस 0;
पूर्ण

काष्ठा dentry *mt76_रेजिस्टर_debugfs(काष्ठा mt76_dev *dev)
अणु
	काष्ठा dentry *dir;

	dir = debugfs_create_dir("mt76", dev->hw->wiphy->debugfsdir);
	अगर (!dir)
		वापस शून्य;

	debugfs_create_u8("led_pin", 0600, dir, &dev->led_pin);
	debugfs_create_u32("regidx", 0600, dir, &dev->debugfs_reg);
	debugfs_create_file_unsafe("regval", 0600, dir, dev,
				   &fops_regval);
	debugfs_create_file_unsafe("napi_threaded", 0600, dir, dev,
				   &fops_napi_thपढ़ोed);
	debugfs_create_blob("eeprom", 0400, dir, &dev->eeprom);
	अगर (dev->otp.data)
		debugfs_create_blob("otp", 0400, dir, &dev->otp);
	debugfs_create_devm_seqfile(dev->dev, "rate_txpower", dir,
				    mt76_पढ़ो_rate_txघातer);
	debugfs_create_devm_seqfile(dev->dev, "rx-queues", dir,
				    mt76_rx_queues_पढ़ो);

	वापस dir;
पूर्ण
EXPORT_SYMBOL_GPL(mt76_रेजिस्टर_debugfs);
