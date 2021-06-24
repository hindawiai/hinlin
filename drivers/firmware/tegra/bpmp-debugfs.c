<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017, NVIDIA CORPORATION.  All rights reserved.
 */
#समावेश <linux/debugfs.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश <soc/tegra/bpmp.h>
#समावेश <soc/tegra/bpmp-abi.h>

अटल DEFINE_MUTEX(bpmp_debug_lock);

काष्ठा seqbuf अणु
	अक्षर *buf;
	माप_प्रकार pos;
	माप_प्रकार size;
पूर्ण;

अटल व्योम seqbuf_init(काष्ठा seqbuf *seqbuf, व्योम *buf, माप_प्रकार size)
अणु
	seqbuf->buf = buf;
	seqbuf->size = size;
	seqbuf->pos = 0;
पूर्ण

अटल माप_प्रकार seqbuf_avail(काष्ठा seqbuf *seqbuf)
अणु
	वापस seqbuf->pos < seqbuf->size ? seqbuf->size - seqbuf->pos : 0;
पूर्ण

अटल माप_प्रकार seqbuf_status(काष्ठा seqbuf *seqbuf)
अणु
	वापस seqbuf->pos <= seqbuf->size ? 0 : -EOVERFLOW;
पूर्ण

अटल पूर्णांक seqbuf_eof(काष्ठा seqbuf *seqbuf)
अणु
	वापस seqbuf->pos >= seqbuf->size;
पूर्ण

अटल पूर्णांक seqbuf_पढ़ो(काष्ठा seqbuf *seqbuf, व्योम *buf, माप_प्रकार nbyte)
अणु
	nbyte = min(nbyte, seqbuf_avail(seqbuf));
	स_नकल(buf, seqbuf->buf + seqbuf->pos, nbyte);
	seqbuf->pos += nbyte;
	वापस seqbuf_status(seqbuf);
पूर्ण

अटल पूर्णांक seqbuf_पढ़ो_u32(काष्ठा seqbuf *seqbuf, uपूर्णांक32_t *v)
अणु
	पूर्णांक err;

	err = seqbuf_पढ़ो(seqbuf, v, 4);
	*v = le32_to_cpu(*v);
	वापस err;
पूर्ण

अटल पूर्णांक seqbuf_पढ़ो_str(काष्ठा seqbuf *seqbuf, स्थिर अक्षर **str)
अणु
	*str = seqbuf->buf + seqbuf->pos;
	seqbuf->pos += strnlen(*str, seqbuf_avail(seqbuf));
	seqbuf->pos++;
	वापस seqbuf_status(seqbuf);
पूर्ण

अटल व्योम seqbuf_seek(काष्ठा seqbuf *seqbuf, sमाप_प्रकार offset)
अणु
	seqbuf->pos += offset;
पूर्ण

/* map filename in Linux debugfs to corresponding entry in BPMP */
अटल स्थिर अक्षर *get_filename(काष्ठा tegra_bpmp *bpmp,
				स्थिर काष्ठा file *file, अक्षर *buf, पूर्णांक size)
अणु
	अक्षर root_path_buf[512];
	स्थिर अक्षर *root_path;
	स्थिर अक्षर *filename;
	माप_प्रकार root_len;

	root_path = dentry_path(bpmp->debugfs_mirror, root_path_buf,
				माप(root_path_buf));
	अगर (IS_ERR(root_path))
		वापस शून्य;

	root_len = म_माप(root_path);

	filename = dentry_path(file->f_path.dentry, buf, size);
	अगर (IS_ERR(filename))
		वापस शून्य;

	अगर (म_माप(filename) < root_len ||
			म_भेदन(filename, root_path, root_len))
		वापस शून्य;

	filename += root_len;

	वापस filename;
पूर्ण

अटल पूर्णांक mrq_debug_खोलो(काष्ठा tegra_bpmp *bpmp, स्थिर अक्षर *name,
			  uपूर्णांक32_t *fd, uपूर्णांक32_t *len, bool ग_लिखो)
अणु
	काष्ठा mrq_debug_request req = अणु
		.cmd = cpu_to_le32(ग_लिखो ? CMD_DEBUG_OPEN_WO : CMD_DEBUG_OPEN_RO),
	पूर्ण;
	काष्ठा mrq_debug_response resp;
	काष्ठा tegra_bpmp_message msg = अणु
		.mrq = MRQ_DEBUG,
		.tx = अणु
			.data = &req,
			.size = माप(req),
		पूर्ण,
		.rx = अणु
			.data = &resp,
			.size = माप(resp),
		पूर्ण,
	पूर्ण;
	sमाप_प्रकार sz_name;
	पूर्णांक err = 0;

	sz_name = strscpy(req.fop.name, name, माप(req.fop.name));
	अगर (sz_name < 0) अणु
		pr_err("File name too large: %s\n", name);
		वापस -EINVAL;
	पूर्ण

	err = tegra_bpmp_transfer(bpmp, &msg);
	अगर (err < 0)
		वापस err;
	अन्यथा अगर (msg.rx.ret < 0)
		वापस -EINVAL;

	*len = resp.fop.datalen;
	*fd = resp.fop.fd;

	वापस 0;
पूर्ण

अटल पूर्णांक mrq_debug_बंद(काष्ठा tegra_bpmp *bpmp, uपूर्णांक32_t fd)
अणु
	काष्ठा mrq_debug_request req = अणु
		.cmd = cpu_to_le32(CMD_DEBUG_CLOSE),
		.frd = अणु
			.fd = fd,
		पूर्ण,
	पूर्ण;
	काष्ठा mrq_debug_response resp;
	काष्ठा tegra_bpmp_message msg = अणु
		.mrq = MRQ_DEBUG,
		.tx = अणु
			.data = &req,
			.size = माप(req),
		पूर्ण,
		.rx = अणु
			.data = &resp,
			.size = माप(resp),
		पूर्ण,
	पूर्ण;
	पूर्णांक err = 0;

	err = tegra_bpmp_transfer(bpmp, &msg);
	अगर (err < 0)
		वापस err;
	अन्यथा अगर (msg.rx.ret < 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक mrq_debug_पढ़ो(काष्ठा tegra_bpmp *bpmp, स्थिर अक्षर *name,
			  अक्षर *data, माप_प्रकार sz_data, uपूर्णांक32_t *nbytes)
अणु
	काष्ठा mrq_debug_request req = अणु
		.cmd = cpu_to_le32(CMD_DEBUG_READ),
	पूर्ण;
	काष्ठा mrq_debug_response resp;
	काष्ठा tegra_bpmp_message msg = अणु
		.mrq = MRQ_DEBUG,
		.tx = अणु
			.data = &req,
			.size = माप(req),
		पूर्ण,
		.rx = अणु
			.data = &resp,
			.size = माप(resp),
		पूर्ण,
	पूर्ण;
	uपूर्णांक32_t fd = 0, len = 0;
	पूर्णांक reमुख्यing, err;

	mutex_lock(&bpmp_debug_lock);
	err = mrq_debug_खोलो(bpmp, name, &fd, &len, 0);
	अगर (err)
		जाओ out;

	अगर (len > sz_data) अणु
		err = -EFBIG;
		जाओ बंद;
	पूर्ण

	req.frd.fd = fd;
	reमुख्यing = len;

	जबतक (reमुख्यing > 0) अणु
		err = tegra_bpmp_transfer(bpmp, &msg);
		अगर (err < 0) अणु
			जाओ बंद;
		पूर्ण अन्यथा अगर (msg.rx.ret < 0) अणु
			err = -EINVAL;
			जाओ बंद;
		पूर्ण

		अगर (resp.frd.पढ़ोlen > reमुख्यing) अणु
			pr_err("%s: read data length invalid\n", __func__);
			err = -EINVAL;
			जाओ बंद;
		पूर्ण

		स_नकल(data, resp.frd.data, resp.frd.पढ़ोlen);
		data += resp.frd.पढ़ोlen;
		reमुख्यing -= resp.frd.पढ़ोlen;
	पूर्ण

	*nbytes = len;

बंद:
	err = mrq_debug_बंद(bpmp, fd);
out:
	mutex_unlock(&bpmp_debug_lock);
	वापस err;
पूर्ण

अटल पूर्णांक mrq_debug_ग_लिखो(काष्ठा tegra_bpmp *bpmp, स्थिर अक्षर *name,
			   uपूर्णांक8_t *data, माप_प्रकार sz_data)
अणु
	काष्ठा mrq_debug_request req = अणु
		.cmd = cpu_to_le32(CMD_DEBUG_WRITE)
	पूर्ण;
	काष्ठा mrq_debug_response resp;
	काष्ठा tegra_bpmp_message msg = अणु
		.mrq = MRQ_DEBUG,
		.tx = अणु
			.data = &req,
			.size = माप(req),
		पूर्ण,
		.rx = अणु
			.data = &resp,
			.size = माप(resp),
		पूर्ण,
	पूर्ण;
	uपूर्णांक32_t fd = 0, len = 0;
	माप_प्रकार reमुख्यing;
	पूर्णांक err;

	mutex_lock(&bpmp_debug_lock);
	err = mrq_debug_खोलो(bpmp, name, &fd, &len, 1);
	अगर (err)
		जाओ out;

	अगर (sz_data > len) अणु
		err = -EINVAL;
		जाओ बंद;
	पूर्ण

	req.fwr.fd = fd;
	reमुख्यing = sz_data;

	जबतक (reमुख्यing > 0) अणु
		len = min(reमुख्यing, माप(req.fwr.data));
		स_नकल(req.fwr.data, data, len);
		req.fwr.datalen = len;

		err = tegra_bpmp_transfer(bpmp, &msg);
		अगर (err < 0) अणु
			जाओ बंद;
		पूर्ण अन्यथा अगर (msg.rx.ret < 0) अणु
			err = -EINVAL;
			जाओ बंद;
		पूर्ण

		data += req.fwr.datalen;
		reमुख्यing -= req.fwr.datalen;
	पूर्ण

बंद:
	err = mrq_debug_बंद(bpmp, fd);
out:
	mutex_unlock(&bpmp_debug_lock);
	वापस err;
पूर्ण

अटल पूर्णांक bpmp_debug_show(काष्ठा seq_file *m, व्योम *p)
अणु
	काष्ठा file *file = m->निजी;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा tegra_bpmp *bpmp = inode->i_निजी;
	अक्षर *databuf = शून्य;
	अक्षर fnamebuf[256];
	स्थिर अक्षर *filename;
	uपूर्णांक32_t nbytes = 0;
	माप_प्रकार len;
	पूर्णांक err;

	len = seq_get_buf(m, &databuf);
	अगर (!databuf)
		वापस -ENOMEM;

	filename = get_filename(bpmp, file, fnamebuf, माप(fnamebuf));
	अगर (!filename)
		वापस -ENOENT;

	err = mrq_debug_पढ़ो(bpmp, filename, databuf, len, &nbytes);
	अगर (!err)
		seq_commit(m, nbytes);

	वापस err;
पूर्ण

अटल sमाप_प्रकार bpmp_debug_store(काष्ठा file *file, स्थिर अक्षर __user *buf,
		माप_प्रकार count, loff_t *f_pos)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा tegra_bpmp *bpmp = inode->i_निजी;
	अक्षर *databuf = शून्य;
	अक्षर fnamebuf[256];
	स्थिर अक्षर *filename;
	sमाप_प्रकार err;

	filename = get_filename(bpmp, file, fnamebuf, माप(fnamebuf));
	अगर (!filename)
		वापस -ENOENT;

	databuf = kदो_स्मृति(count, GFP_KERNEL);
	अगर (!databuf)
		वापस -ENOMEM;

	अगर (copy_from_user(databuf, buf, count)) अणु
		err = -EFAULT;
		जाओ मुक्त_ret;
	पूर्ण

	err = mrq_debug_ग_लिखो(bpmp, filename, databuf, count);

मुक्त_ret:
	kमुक्त(databuf);

	वापस err ?: count;
पूर्ण

अटल पूर्णांक bpmp_debug_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो_size(file, bpmp_debug_show, file, SZ_256K);
पूर्ण

अटल स्थिर काष्ठा file_operations bpmp_debug_fops = अणु
	.खोलो		= bpmp_debug_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.ग_लिखो		= bpmp_debug_store,
	.release	= single_release,
पूर्ण;

अटल पूर्णांक bpmp_populate_debugfs_inband(काष्ठा tegra_bpmp *bpmp,
					काष्ठा dentry *parent,
					अक्षर *ppath)
अणु
	स्थिर माप_प्रकार pathlen = SZ_256;
	स्थिर माप_प्रकार bufsize = SZ_16K;
	uपूर्णांक32_t dsize, attrs = 0;
	काष्ठा dentry *dentry;
	काष्ठा seqbuf seqbuf;
	अक्षर *buf, *pathbuf;
	स्थिर अक्षर *name;
	पूर्णांक err = 0;

	अगर (!bpmp || !parent || !ppath)
		वापस -EINVAL;

	buf = kदो_स्मृति(bufsize, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	pathbuf = kzalloc(pathlen, GFP_KERNEL);
	अगर (!pathbuf) अणु
		kमुक्त(buf);
		वापस -ENOMEM;
	पूर्ण

	err = mrq_debug_पढ़ो(bpmp, ppath, buf, bufsize, &dsize);
	अगर (err)
		जाओ out;

	seqbuf_init(&seqbuf, buf, dsize);

	जबतक (!seqbuf_eof(&seqbuf)) अणु
		err = seqbuf_पढ़ो_u32(&seqbuf, &attrs);
		अगर (err)
			जाओ out;

		err = seqbuf_पढ़ो_str(&seqbuf, &name);
		अगर (err < 0)
			जाओ out;

		अगर (attrs & DEBUGFS_S_ISसूची) अणु
			माप_प्रकार len;

			dentry = debugfs_create_dir(name, parent);
			अगर (IS_ERR(dentry)) अणु
				err = PTR_ERR(dentry);
				जाओ out;
			पूर्ण

			len = snम_लिखो(pathbuf, pathlen, "%s%s/", ppath, name);
			अगर (len >= pathlen) अणु
				err = -EINVAL;
				जाओ out;
			पूर्ण

			err = bpmp_populate_debugfs_inband(bpmp, dentry,
							   pathbuf);
			अगर (err < 0)
				जाओ out;
		पूर्ण अन्यथा अणु
			umode_t mode;

			mode = attrs & DEBUGFS_S_IRUSR ? 0400 : 0;
			mode |= attrs & DEBUGFS_S_IWUSR ? 0200 : 0;
			dentry = debugfs_create_file(name, mode, parent, bpmp,
						     &bpmp_debug_fops);
			अगर (!dentry) अणु
				err = -ENOMEM;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

out:
	kमुक्त(pathbuf);
	kमुक्त(buf);

	वापस err;
पूर्ण

अटल पूर्णांक mrq_debugfs_पढ़ो(काष्ठा tegra_bpmp *bpmp,
			    dma_addr_t name, माप_प्रकार sz_name,
			    dma_addr_t data, माप_प्रकार sz_data,
			    माप_प्रकार *nbytes)
अणु
	काष्ठा mrq_debugfs_request req = अणु
		.cmd = cpu_to_le32(CMD_DEBUGFS_READ),
		.fop = अणु
			.fnameaddr = cpu_to_le32((uपूर्णांक32_t)name),
			.fnamelen = cpu_to_le32((uपूर्णांक32_t)sz_name),
			.dataaddr = cpu_to_le32((uपूर्णांक32_t)data),
			.datalen = cpu_to_le32((uपूर्णांक32_t)sz_data),
		पूर्ण,
	पूर्ण;
	काष्ठा mrq_debugfs_response resp;
	काष्ठा tegra_bpmp_message msg = अणु
		.mrq = MRQ_DEBUGFS,
		.tx = अणु
			.data = &req,
			.size = माप(req),
		पूर्ण,
		.rx = अणु
			.data = &resp,
			.size = माप(resp),
		पूर्ण,
	पूर्ण;
	पूर्णांक err;

	err = tegra_bpmp_transfer(bpmp, &msg);
	अगर (err < 0)
		वापस err;
	अन्यथा अगर (msg.rx.ret < 0)
		वापस -EINVAL;

	*nbytes = (माप_प्रकार)resp.fop.nbytes;

	वापस 0;
पूर्ण

अटल पूर्णांक mrq_debugfs_ग_लिखो(काष्ठा tegra_bpmp *bpmp,
			     dma_addr_t name, माप_प्रकार sz_name,
			     dma_addr_t data, माप_प्रकार sz_data)
अणु
	स्थिर काष्ठा mrq_debugfs_request req = अणु
		.cmd = cpu_to_le32(CMD_DEBUGFS_WRITE),
		.fop = अणु
			.fnameaddr = cpu_to_le32((uपूर्णांक32_t)name),
			.fnamelen = cpu_to_le32((uपूर्णांक32_t)sz_name),
			.dataaddr = cpu_to_le32((uपूर्णांक32_t)data),
			.datalen = cpu_to_le32((uपूर्णांक32_t)sz_data),
		पूर्ण,
	पूर्ण;
	काष्ठा tegra_bpmp_message msg = अणु
		.mrq = MRQ_DEBUGFS,
		.tx = अणु
			.data = &req,
			.size = माप(req),
		पूर्ण,
	पूर्ण;

	वापस tegra_bpmp_transfer(bpmp, &msg);
पूर्ण

अटल पूर्णांक mrq_debugfs_dumpdir(काष्ठा tegra_bpmp *bpmp, dma_addr_t addr,
			       माप_प्रकार size, माप_प्रकार *nbytes)
अणु
	स्थिर काष्ठा mrq_debugfs_request req = अणु
		.cmd = cpu_to_le32(CMD_DEBUGFS_DUMPसूची),
		.dumpdir = अणु
			.dataaddr = cpu_to_le32((uपूर्णांक32_t)addr),
			.datalen = cpu_to_le32((uपूर्णांक32_t)size),
		पूर्ण,
	पूर्ण;
	काष्ठा mrq_debugfs_response resp;
	काष्ठा tegra_bpmp_message msg = अणु
		.mrq = MRQ_DEBUGFS,
		.tx = अणु
			.data = &req,
			.size = माप(req),
		पूर्ण,
		.rx = अणु
			.data = &resp,
			.size = माप(resp),
		पूर्ण,
	पूर्ण;
	पूर्णांक err;

	err = tegra_bpmp_transfer(bpmp, &msg);
	अगर (err < 0)
		वापस err;
	अन्यथा अगर (msg.rx.ret < 0)
		वापस -EINVAL;

	*nbytes = (माप_प्रकार)resp.dumpdir.nbytes;

	वापस 0;
पूर्ण

अटल पूर्णांक debugfs_show(काष्ठा seq_file *m, व्योम *p)
अणु
	काष्ठा file *file = m->निजी;
	काष्ठा inode *inode = file_inode(file);
	काष्ठा tegra_bpmp *bpmp = inode->i_निजी;
	स्थिर माप_प्रकार datasize = m->size;
	स्थिर माप_प्रकार namesize = SZ_256;
	व्योम *datavirt, *namevirt;
	dma_addr_t dataphys, namephys;
	अक्षर buf[256];
	स्थिर अक्षर *filename;
	माप_प्रकार len, nbytes;
	पूर्णांक err;

	filename = get_filename(bpmp, file, buf, माप(buf));
	अगर (!filename)
		वापस -ENOENT;

	namevirt = dma_alloc_coherent(bpmp->dev, namesize, &namephys,
				      GFP_KERNEL | GFP_DMA32);
	अगर (!namevirt)
		वापस -ENOMEM;

	datavirt = dma_alloc_coherent(bpmp->dev, datasize, &dataphys,
				      GFP_KERNEL | GFP_DMA32);
	अगर (!datavirt) अणु
		err = -ENOMEM;
		जाओ मुक्त_namebuf;
	पूर्ण

	len = म_माप(filename);
	म_नकलन(namevirt, filename, namesize);

	err = mrq_debugfs_पढ़ो(bpmp, namephys, len, dataphys, datasize,
			       &nbytes);

	अगर (!err)
		seq_ग_लिखो(m, datavirt, nbytes);

	dma_मुक्त_coherent(bpmp->dev, datasize, datavirt, dataphys);
मुक्त_namebuf:
	dma_मुक्त_coherent(bpmp->dev, namesize, namevirt, namephys);

	वापस err;
पूर्ण

अटल पूर्णांक debugfs_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो_size(file, debugfs_show, file, SZ_128K);
पूर्ण

अटल sमाप_प्रकार debugfs_store(काष्ठा file *file, स्थिर अक्षर __user *buf,
		माप_प्रकार count, loff_t *f_pos)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा tegra_bpmp *bpmp = inode->i_निजी;
	स्थिर माप_प्रकार datasize = count;
	स्थिर माप_प्रकार namesize = SZ_256;
	व्योम *datavirt, *namevirt;
	dma_addr_t dataphys, namephys;
	अक्षर fnamebuf[256];
	स्थिर अक्षर *filename;
	माप_प्रकार len;
	पूर्णांक err;

	filename = get_filename(bpmp, file, fnamebuf, माप(fnamebuf));
	अगर (!filename)
		वापस -ENOENT;

	namevirt = dma_alloc_coherent(bpmp->dev, namesize, &namephys,
				      GFP_KERNEL | GFP_DMA32);
	अगर (!namevirt)
		वापस -ENOMEM;

	datavirt = dma_alloc_coherent(bpmp->dev, datasize, &dataphys,
				      GFP_KERNEL | GFP_DMA32);
	अगर (!datavirt) अणु
		err = -ENOMEM;
		जाओ मुक्त_namebuf;
	पूर्ण

	len = म_माप(filename);
	म_नकलन(namevirt, filename, namesize);

	अगर (copy_from_user(datavirt, buf, count)) अणु
		err = -EFAULT;
		जाओ मुक्त_databuf;
	पूर्ण

	err = mrq_debugfs_ग_लिखो(bpmp, namephys, len, dataphys,
				count);

मुक्त_databuf:
	dma_मुक्त_coherent(bpmp->dev, datasize, datavirt, dataphys);
मुक्त_namebuf:
	dma_मुक्त_coherent(bpmp->dev, namesize, namevirt, namephys);

	वापस err ?: count;
पूर्ण

अटल स्थिर काष्ठा file_operations debugfs_fops = अणु
	.खोलो		= debugfs_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.ग_लिखो		= debugfs_store,
	.release	= single_release,
पूर्ण;

अटल पूर्णांक bpmp_populate_dir(काष्ठा tegra_bpmp *bpmp, काष्ठा seqbuf *seqbuf,
			     काष्ठा dentry *parent, uपूर्णांक32_t depth)
अणु
	पूर्णांक err;
	uपूर्णांक32_t d, t;
	स्थिर अक्षर *name;
	काष्ठा dentry *dentry;

	जबतक (!seqbuf_eof(seqbuf)) अणु
		err = seqbuf_पढ़ो_u32(seqbuf, &d);
		अगर (err < 0)
			वापस err;

		अगर (d < depth) अणु
			seqbuf_seek(seqbuf, -4);
			/* go up a level */
			वापस 0;
		पूर्ण अन्यथा अगर (d != depth) अणु
			/* malक्रमmed data received from BPMP */
			वापस -EIO;
		पूर्ण

		err = seqbuf_पढ़ो_u32(seqbuf, &t);
		अगर (err < 0)
			वापस err;
		err = seqbuf_पढ़ो_str(seqbuf, &name);
		अगर (err < 0)
			वापस err;

		अगर (t & DEBUGFS_S_ISसूची) अणु
			dentry = debugfs_create_dir(name, parent);
			अगर (!dentry)
				वापस -ENOMEM;
			err = bpmp_populate_dir(bpmp, seqbuf, dentry, depth+1);
			अगर (err < 0)
				वापस err;
		पूर्ण अन्यथा अणु
			umode_t mode;

			mode = t & DEBUGFS_S_IRUSR ? S_IRUSR : 0;
			mode |= t & DEBUGFS_S_IWUSR ? S_IWUSR : 0;
			dentry = debugfs_create_file(name, mode,
						     parent, bpmp,
						     &debugfs_fops);
			अगर (!dentry)
				वापस -ENOMEM;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bpmp_populate_debugfs_shmem(काष्ठा tegra_bpmp *bpmp)
अणु
	काष्ठा seqbuf seqbuf;
	स्थिर माप_प्रकार sz = SZ_512K;
	dma_addr_t phys;
	माप_प्रकार nbytes;
	व्योम *virt;
	पूर्णांक err;

	virt = dma_alloc_coherent(bpmp->dev, sz, &phys,
				  GFP_KERNEL | GFP_DMA32);
	अगर (!virt)
		वापस -ENOMEM;

	err = mrq_debugfs_dumpdir(bpmp, phys, sz, &nbytes);
	अगर (err < 0) अणु
		जाओ मुक्त;
	पूर्ण अन्यथा अगर (nbytes > sz) अणु
		err = -EINVAL;
		जाओ मुक्त;
	पूर्ण

	seqbuf_init(&seqbuf, virt, nbytes);
	err = bpmp_populate_dir(bpmp, &seqbuf, bpmp->debugfs_mirror, 0);
मुक्त:
	dma_मुक्त_coherent(bpmp->dev, sz, virt, phys);

	वापस err;
पूर्ण

पूर्णांक tegra_bpmp_init_debugfs(काष्ठा tegra_bpmp *bpmp)
अणु
	काष्ठा dentry *root;
	bool inband;
	पूर्णांक err;

	inband = tegra_bpmp_mrq_is_supported(bpmp, MRQ_DEBUG);

	अगर (!inband && !tegra_bpmp_mrq_is_supported(bpmp, MRQ_DEBUGFS))
		वापस 0;

	root = debugfs_create_dir("bpmp", शून्य);
	अगर (!root)
		वापस -ENOMEM;

	bpmp->debugfs_mirror = debugfs_create_dir("debug", root);
	अगर (!bpmp->debugfs_mirror) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (inband)
		err = bpmp_populate_debugfs_inband(bpmp, bpmp->debugfs_mirror,
						   "/");
	अन्यथा
		err = bpmp_populate_debugfs_shmem(bpmp);

out:
	अगर (err < 0)
		debugfs_हटाओ_recursive(root);

	वापस err;
पूर्ण
