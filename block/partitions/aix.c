<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  fs/partitions/aix.c
 *
 *  Copyright (C) 2012-2013 Philippe De Muyter <phdm@macqel.be>
 */

#समावेश "check.h"

काष्ठा lvm_rec अणु
	अक्षर lvm_id[4]; /* "_LVM" */
	अक्षर reserved4[16];
	__be32 lvmarea_len;
	__be32 vgda_len;
	__be32 vgda_psn[2];
	अक्षर reserved36[10];
	__be16 pp_size; /* log2(pp_size) */
	अक्षर reserved46[12];
	__be16 version;
	पूर्ण;

काष्ठा vgda अणु
	__be32 secs;
	__be32 usec;
	अक्षर reserved8[16];
	__be16 numlvs;
	__be16 maxlvs;
	__be16 pp_size;
	__be16 numpvs;
	__be16 total_vgdas;
	__be16 vgda_size;
	पूर्ण;

काष्ठा lvd अणु
	__be16 lv_ix;
	__be16 res2;
	__be16 res4;
	__be16 maxsize;
	__be16 lv_state;
	__be16 mirror;
	__be16 mirror_policy;
	__be16 num_lps;
	__be16 res10[8];
	पूर्ण;

काष्ठा lvname अणु
	अक्षर name[64];
	पूर्ण;

काष्ठा ppe अणु
	__be16 lv_ix;
	अचिन्हित लघु res2;
	अचिन्हित लघु res4;
	__be16 lp_ix;
	अचिन्हित लघु res8[12];
	पूर्ण;

काष्ठा pvd अणु
	अक्षर reserved0[16];
	__be16 pp_count;
	अक्षर reserved18[2];
	__be32 psn_part1;
	अक्षर reserved24[8];
	काष्ठा ppe ppe[1016];
	पूर्ण;

#घोषणा LVM_MAXLVS 256

/**
 * last_lba(): वापस number of last logical block of device
 * @bdev: block device
 *
 * Description: Returns last LBA value on success, 0 on error.
 * This is stored (by sd and ide-geometry) in
 *  the part[0] entry क्रम this disk, and is the number of
 *  physical sectors available on the disk.
 */
अटल u64 last_lba(काष्ठा block_device *bdev)
अणु
	अगर (!bdev || !bdev->bd_inode)
		वापस 0;
	वापस (bdev->bd_inode->i_size >> 9) - 1ULL;
पूर्ण

/**
 * पढ़ो_lba(): Read bytes from disk, starting at given LBA
 * @state
 * @lba
 * @buffer
 * @count
 *
 * Description:  Reads @count bytes from @state->bdev पूर्णांकo @buffer.
 * Returns number of bytes पढ़ो on success, 0 on error.
 */
अटल माप_प्रकार पढ़ो_lba(काष्ठा parsed_partitions *state, u64 lba, u8 *buffer,
			माप_प्रकार count)
अणु
	माप_प्रकार totalपढ़ोcount = 0;

	अगर (!buffer || lba + count / 512 > last_lba(state->bdev))
		वापस 0;

	जबतक (count) अणु
		पूर्णांक copied = 512;
		Sector sect;
		अचिन्हित अक्षर *data = पढ़ो_part_sector(state, lba++, &sect);
		अगर (!data)
			अवरोध;
		अगर (copied > count)
			copied = count;
		स_नकल(buffer, data, copied);
		put_dev_sector(sect);
		buffer += copied;
		totalपढ़ोcount += copied;
		count -= copied;
	पूर्ण
	वापस totalपढ़ोcount;
पूर्ण

/**
 * alloc_pvd(): पढ़ोs physical volume descriptor
 * @state
 * @lba
 *
 * Description: Returns pvd on success,  शून्य on error.
 * Allocates space क्रम pvd and fill it with disk blocks at @lba
 * Notes: remember to मुक्त pvd when you're करोne!
 */
अटल काष्ठा pvd *alloc_pvd(काष्ठा parsed_partitions *state, u32 lba)
अणु
	माप_प्रकार count = माप(काष्ठा pvd);
	काष्ठा pvd *p;

	p = kदो_स्मृति(count, GFP_KERNEL);
	अगर (!p)
		वापस शून्य;

	अगर (पढ़ो_lba(state, lba, (u8 *) p, count) < count) अणु
		kमुक्त(p);
		वापस शून्य;
	पूर्ण
	वापस p;
पूर्ण

/**
 * alloc_lvn(): पढ़ोs logical volume names
 * @state
 * @lba
 *
 * Description: Returns lvn on success,  शून्य on error.
 * Allocates space क्रम lvn and fill it with disk blocks at @lba
 * Notes: remember to मुक्त lvn when you're करोne!
 */
अटल काष्ठा lvname *alloc_lvn(काष्ठा parsed_partitions *state, u32 lba)
अणु
	माप_प्रकार count = माप(काष्ठा lvname) * LVM_MAXLVS;
	काष्ठा lvname *p;

	p = kदो_स्मृति(count, GFP_KERNEL);
	अगर (!p)
		वापस शून्य;

	अगर (पढ़ो_lba(state, lba, (u8 *) p, count) < count) अणु
		kमुक्त(p);
		वापस शून्य;
	पूर्ण
	वापस p;
पूर्ण

पूर्णांक aix_partition(काष्ठा parsed_partitions *state)
अणु
	पूर्णांक ret = 0;
	Sector sect;
	अचिन्हित अक्षर *d;
	u32 pp_bytes_size;
	u32 pp_blocks_size = 0;
	u32 vgda_sector = 0;
	u32 vgda_len = 0;
	पूर्णांक numlvs = 0;
	काष्ठा pvd *pvd = शून्य;
	काष्ठा lv_info अणु
		अचिन्हित लघु pps_per_lv;
		अचिन्हित लघु pps_found;
		अचिन्हित अक्षर lv_is_contiguous;
	पूर्ण *lvip;
	काष्ठा lvname *n = शून्य;

	d = पढ़ो_part_sector(state, 7, &sect);
	अगर (d) अणु
		काष्ठा lvm_rec *p = (काष्ठा lvm_rec *)d;
		u16 lvm_version = be16_to_cpu(p->version);
		अक्षर पंचांगp[64];

		अगर (lvm_version == 1) अणु
			पूर्णांक pp_size_log2 = be16_to_cpu(p->pp_size);

			pp_bytes_size = 1 << pp_size_log2;
			pp_blocks_size = pp_bytes_size / 512;
			snम_लिखो(पंचांगp, माप(पंचांगp),
				" AIX LVM header version %u found\n",
				lvm_version);
			vgda_len = be32_to_cpu(p->vgda_len);
			vgda_sector = be32_to_cpu(p->vgda_psn[0]);
		पूर्ण अन्यथा अणु
			snम_लिखो(पंचांगp, माप(पंचांगp),
				" unsupported AIX LVM version %d found\n",
				lvm_version);
		पूर्ण
		strlcat(state->pp_buf, पंचांगp, PAGE_SIZE);
		put_dev_sector(sect);
	पूर्ण
	अगर (vgda_sector && (d = पढ़ो_part_sector(state, vgda_sector, &sect))) अणु
		काष्ठा vgda *p = (काष्ठा vgda *)d;

		numlvs = be16_to_cpu(p->numlvs);
		put_dev_sector(sect);
	पूर्ण
	lvip = kसुस्मृति(state->limit, माप(काष्ठा lv_info), GFP_KERNEL);
	अगर (!lvip)
		वापस 0;
	अगर (numlvs && (d = पढ़ो_part_sector(state, vgda_sector + 1, &sect))) अणु
		काष्ठा lvd *p = (काष्ठा lvd *)d;
		पूर्णांक i;

		n = alloc_lvn(state, vgda_sector + vgda_len - 33);
		अगर (n) अणु
			पूर्णांक foundlvs = 0;

			क्रम (i = 0; foundlvs < numlvs && i < state->limit; i += 1) अणु
				lvip[i].pps_per_lv = be16_to_cpu(p[i].num_lps);
				अगर (lvip[i].pps_per_lv)
					foundlvs += 1;
			पूर्ण
			/* pvd loops depend on n[].name and lvip[].pps_per_lv */
			pvd = alloc_pvd(state, vgda_sector + 17);
		पूर्ण
		put_dev_sector(sect);
	पूर्ण
	अगर (pvd) अणु
		पूर्णांक numpps = be16_to_cpu(pvd->pp_count);
		पूर्णांक psn_part1 = be32_to_cpu(pvd->psn_part1);
		पूर्णांक i;
		पूर्णांक cur_lv_ix = -1;
		पूर्णांक next_lp_ix = 1;
		पूर्णांक lp_ix;

		क्रम (i = 0; i < numpps; i += 1) अणु
			काष्ठा ppe *p = pvd->ppe + i;
			अचिन्हित पूर्णांक lv_ix;

			lp_ix = be16_to_cpu(p->lp_ix);
			अगर (!lp_ix) अणु
				next_lp_ix = 1;
				जारी;
			पूर्ण
			lv_ix = be16_to_cpu(p->lv_ix) - 1;
			अगर (lv_ix >= state->limit) अणु
				cur_lv_ix = -1;
				जारी;
			पूर्ण
			lvip[lv_ix].pps_found += 1;
			अगर (lp_ix == 1) अणु
				cur_lv_ix = lv_ix;
				next_lp_ix = 1;
			पूर्ण अन्यथा अगर (lv_ix != cur_lv_ix || lp_ix != next_lp_ix) अणु
				next_lp_ix = 1;
				जारी;
			पूर्ण
			अगर (lp_ix == lvip[lv_ix].pps_per_lv) अणु
				अक्षर पंचांगp[70];

				put_partition(state, lv_ix + 1,
				  (i + 1 - lp_ix) * pp_blocks_size + psn_part1,
				  lvip[lv_ix].pps_per_lv * pp_blocks_size);
				snम_लिखो(पंचांगp, माप(पंचांगp), " <%s>\n",
					 n[lv_ix].name);
				strlcat(state->pp_buf, पंचांगp, PAGE_SIZE);
				lvip[lv_ix].lv_is_contiguous = 1;
				ret = 1;
				next_lp_ix = 1;
			पूर्ण अन्यथा
				next_lp_ix += 1;
		पूर्ण
		क्रम (i = 0; i < state->limit; i += 1)
			अगर (lvip[i].pps_found && !lvip[i].lv_is_contiguous) अणु
				अक्षर पंचांगp[माप(n[i].name) + 1]; // null अक्षर

				snम_लिखो(पंचांगp, माप(पंचांगp), "%s", n[i].name);
				pr_warn("partition %s (%u pp's found) is "
					"not contiguous\n",
					पंचांगp, lvip[i].pps_found);
			पूर्ण
		kमुक्त(pvd);
	पूर्ण
	kमुक्त(n);
	kमुक्त(lvip);
	वापस ret;
पूर्ण
