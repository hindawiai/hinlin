<शैली गुरु>
// SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only)
/* Copyright(c) 2014 - 2020 Intel Corporation */
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/seq_file.h>
#समावेश "adf_accel_devices.h"
#समावेश "adf_transport_internal.h"
#समावेश "adf_transport_access_macros.h"

अटल DEFINE_MUTEX(ring_पढ़ो_lock);
अटल DEFINE_MUTEX(bank_पढ़ो_lock);

अटल व्योम *adf_ring_start(काष्ठा seq_file *sfile, loff_t *pos)
अणु
	काष्ठा adf_etr_ring_data *ring = sfile->निजी;

	mutex_lock(&ring_पढ़ो_lock);
	अगर (*pos == 0)
		वापस SEQ_START_TOKEN;

	अगर (*pos >= (ADF_SIZE_TO_RING_SIZE_IN_BYTES(ring->ring_size) /
		     ADF_MSG_SIZE_TO_BYTES(ring->msg_size)))
		वापस शून्य;

	वापस ring->base_addr +
		(ADF_MSG_SIZE_TO_BYTES(ring->msg_size) * (*pos)++);
पूर्ण

अटल व्योम *adf_ring_next(काष्ठा seq_file *sfile, व्योम *v, loff_t *pos)
अणु
	काष्ठा adf_etr_ring_data *ring = sfile->निजी;

	अगर (*pos >= (ADF_SIZE_TO_RING_SIZE_IN_BYTES(ring->ring_size) /
		     ADF_MSG_SIZE_TO_BYTES(ring->msg_size)))
		वापस शून्य;

	वापस ring->base_addr +
		(ADF_MSG_SIZE_TO_BYTES(ring->msg_size) * (*pos)++);
पूर्ण

अटल पूर्णांक adf_ring_show(काष्ठा seq_file *sfile, व्योम *v)
अणु
	काष्ठा adf_etr_ring_data *ring = sfile->निजी;
	काष्ठा adf_etr_bank_data *bank = ring->bank;
	काष्ठा adf_hw_csr_ops *csr_ops = GET_CSR_OPS(bank->accel_dev);
	व्योम __iomem *csr = ring->bank->csr_addr;

	अगर (v == SEQ_START_TOKEN) अणु
		पूर्णांक head, tail, empty;

		head = csr_ops->पढ़ो_csr_ring_head(csr, bank->bank_number,
						   ring->ring_number);
		tail = csr_ops->पढ़ो_csr_ring_tail(csr, bank->bank_number,
						   ring->ring_number);
		empty = csr_ops->पढ़ो_csr_e_stat(csr, bank->bank_number);

		seq_माला_दो(sfile, "------- Ring configuration -------\n");
		seq_म_लिखो(sfile, "ring name: %s\n",
			   ring->ring_debug->ring_name);
		seq_म_लिखो(sfile, "ring num %d, bank num %d\n",
			   ring->ring_number, ring->bank->bank_number);
		seq_म_लिखो(sfile, "head %x, tail %x, empty: %d\n",
			   head, tail, (empty & 1 << ring->ring_number)
			   >> ring->ring_number);
		seq_म_लिखो(sfile, "ring size %lld, msg size %d\n",
			   (दीर्घ दीर्घ)ADF_SIZE_TO_RING_SIZE_IN_BYTES(ring->ring_size),
			   ADF_MSG_SIZE_TO_BYTES(ring->msg_size));
		seq_माला_दो(sfile, "----------- Ring data ------------\n");
		वापस 0;
	पूर्ण
	seq_hex_dump(sfile, "", DUMP_PREFIX_ADDRESS, 32, 4,
		     v, ADF_MSG_SIZE_TO_BYTES(ring->msg_size), false);
	वापस 0;
पूर्ण

अटल व्योम adf_ring_stop(काष्ठा seq_file *sfile, व्योम *v)
अणु
	mutex_unlock(&ring_पढ़ो_lock);
पूर्ण

अटल स्थिर काष्ठा seq_operations adf_ring_debug_sops = अणु
	.start = adf_ring_start,
	.next = adf_ring_next,
	.stop = adf_ring_stop,
	.show = adf_ring_show
पूर्ण;

DEFINE_SEQ_ATTRIBUTE(adf_ring_debug);

पूर्णांक adf_ring_debugfs_add(काष्ठा adf_etr_ring_data *ring, स्थिर अक्षर *name)
अणु
	काष्ठा adf_etr_ring_debug_entry *ring_debug;
	अक्षर entry_name[8];

	ring_debug = kzalloc(माप(*ring_debug), GFP_KERNEL);
	अगर (!ring_debug)
		वापस -ENOMEM;

	strlcpy(ring_debug->ring_name, name, माप(ring_debug->ring_name));
	snम_लिखो(entry_name, माप(entry_name), "ring_%02d",
		 ring->ring_number);

	ring_debug->debug = debugfs_create_file(entry_name, S_IRUSR,
						ring->bank->bank_debug_dir,
						ring, &adf_ring_debug_fops);
	ring->ring_debug = ring_debug;
	वापस 0;
पूर्ण

व्योम adf_ring_debugfs_rm(काष्ठा adf_etr_ring_data *ring)
अणु
	अगर (ring->ring_debug) अणु
		debugfs_हटाओ(ring->ring_debug->debug);
		kमुक्त(ring->ring_debug);
		ring->ring_debug = शून्य;
	पूर्ण
पूर्ण

अटल व्योम *adf_bank_start(काष्ठा seq_file *sfile, loff_t *pos)
अणु
	काष्ठा adf_etr_bank_data *bank = sfile->निजी;
	u8 num_rings_per_bank = GET_NUM_RINGS_PER_BANK(bank->accel_dev);

	mutex_lock(&bank_पढ़ो_lock);
	अगर (*pos == 0)
		वापस SEQ_START_TOKEN;

	अगर (*pos >= num_rings_per_bank)
		वापस शून्य;

	वापस pos;
पूर्ण

अटल व्योम *adf_bank_next(काष्ठा seq_file *sfile, व्योम *v, loff_t *pos)
अणु
	काष्ठा adf_etr_bank_data *bank = sfile->निजी;
	u8 num_rings_per_bank = GET_NUM_RINGS_PER_BANK(bank->accel_dev);

	अगर (++(*pos) >= num_rings_per_bank)
		वापस शून्य;

	वापस pos;
पूर्ण

अटल पूर्णांक adf_bank_show(काष्ठा seq_file *sfile, व्योम *v)
अणु
	काष्ठा adf_etr_bank_data *bank = sfile->निजी;
	काष्ठा adf_hw_csr_ops *csr_ops = GET_CSR_OPS(bank->accel_dev);

	अगर (v == SEQ_START_TOKEN) अणु
		seq_म_लिखो(sfile, "------- Bank %d configuration -------\n",
			   bank->bank_number);
	पूर्ण अन्यथा अणु
		पूर्णांक ring_id = *((पूर्णांक *)v) - 1;
		काष्ठा adf_etr_ring_data *ring = &bank->rings[ring_id];
		व्योम __iomem *csr = bank->csr_addr;
		पूर्णांक head, tail, empty;

		अगर (!(bank->ring_mask & 1 << ring_id))
			वापस 0;

		head = csr_ops->पढ़ो_csr_ring_head(csr, bank->bank_number,
						   ring->ring_number);
		tail = csr_ops->पढ़ो_csr_ring_tail(csr, bank->bank_number,
						   ring->ring_number);
		empty = csr_ops->पढ़ो_csr_e_stat(csr, bank->bank_number);

		seq_म_लिखो(sfile,
			   "ring num %02d, head %04x, tail %04x, empty: %d\n",
			   ring->ring_number, head, tail,
			   (empty & 1 << ring->ring_number) >>
			   ring->ring_number);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम adf_bank_stop(काष्ठा seq_file *sfile, व्योम *v)
अणु
	mutex_unlock(&bank_पढ़ो_lock);
पूर्ण

अटल स्थिर काष्ठा seq_operations adf_bank_debug_sops = अणु
	.start = adf_bank_start,
	.next = adf_bank_next,
	.stop = adf_bank_stop,
	.show = adf_bank_show
पूर्ण;

DEFINE_SEQ_ATTRIBUTE(adf_bank_debug);

पूर्णांक adf_bank_debugfs_add(काष्ठा adf_etr_bank_data *bank)
अणु
	काष्ठा adf_accel_dev *accel_dev = bank->accel_dev;
	काष्ठा dentry *parent = accel_dev->transport->debug;
	अक्षर name[8];

	snम_लिखो(name, माप(name), "bank_%02d", bank->bank_number);
	bank->bank_debug_dir = debugfs_create_dir(name, parent);
	bank->bank_debug_cfg = debugfs_create_file("config", S_IRUSR,
						   bank->bank_debug_dir, bank,
						   &adf_bank_debug_fops);
	वापस 0;
पूर्ण

व्योम adf_bank_debugfs_rm(काष्ठा adf_etr_bank_data *bank)
अणु
	debugfs_हटाओ(bank->bank_debug_cfg);
	debugfs_हटाओ(bank->bank_debug_dir);
पूर्ण
