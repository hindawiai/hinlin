<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Simple test of virtio code, entirely in userpsace. */
#घोषणा _GNU_SOURCE
#समावेश <sched.h>
#समावेश <err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/virtपन.स>
#समावेश <linux/vringh.h>
#समावेश <linux/virtio_ring.h>
#समावेश <linux/virtio_config.h>
#समावेश <linux/uaccess.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/mman.h>
#समावेश <sys/रुको.h>
#समावेश <fcntl.h>

#घोषणा USER_MEM (1024*1024)
व्योम *__user_addr_min, *__user_addr_max;
व्योम *__kदो_स्मृति_fake, *__kमुक्त_ignore_start, *__kमुक्त_ignore_end;
अटल u64 user_addr_offset;

#घोषणा RINGSIZE 256
#घोषणा ALIGN 4096

अटल bool never_notअगरy_host(काष्ठा virtqueue *vq)
अणु
	पात();
पूर्ण

अटल व्योम never_callback_guest(काष्ठा virtqueue *vq)
अणु
	पात();
पूर्ण

अटल bool getrange_iov(काष्ठा vringh *vrh, u64 addr, काष्ठा vringh_range *r)
अणु
	अगर (addr < (u64)(अचिन्हित दीर्घ)__user_addr_min - user_addr_offset)
		वापस false;
	अगर (addr >= (u64)(अचिन्हित दीर्घ)__user_addr_max - user_addr_offset)
		वापस false;

	r->start = (u64)(अचिन्हित दीर्घ)__user_addr_min - user_addr_offset;
	r->end_incl = (u64)(अचिन्हित दीर्घ)__user_addr_max - 1 - user_addr_offset;
	r->offset = user_addr_offset;
	वापस true;
पूर्ण

/* We वापस single byte ranges. */
अटल bool getrange_slow(काष्ठा vringh *vrh, u64 addr, काष्ठा vringh_range *r)
अणु
	अगर (addr < (u64)(अचिन्हित दीर्घ)__user_addr_min - user_addr_offset)
		वापस false;
	अगर (addr >= (u64)(अचिन्हित दीर्घ)__user_addr_max - user_addr_offset)
		वापस false;

	r->start = addr;
	r->end_incl = r->start;
	r->offset = user_addr_offset;
	वापस true;
पूर्ण

काष्ठा guest_virtio_device अणु
	काष्ठा virtio_device vdev;
	पूर्णांक to_host_fd;
	अचिन्हित दीर्घ notअगरies;
पूर्ण;

अटल bool parallel_notअगरy_host(काष्ठा virtqueue *vq)
अणु
	पूर्णांक rc;
	काष्ठा guest_virtio_device *gvdev;

	gvdev = container_of(vq->vdev, काष्ठा guest_virtio_device, vdev);
	rc = ग_लिखो(gvdev->to_host_fd, "", 1);
	अगर (rc < 0)
		वापस false;
	gvdev->notअगरies++;
	वापस true;
पूर्ण

अटल bool no_notअगरy_host(काष्ठा virtqueue *vq)
अणु
	वापस true;
पूर्ण

#घोषणा NUM_XFERS (10000000)

/* We aim क्रम two "distant" cpus. */
अटल व्योम find_cpus(अचिन्हित पूर्णांक *first, अचिन्हित पूर्णांक *last)
अणु
	अचिन्हित पूर्णांक i;

	*first = -1U;
	*last = 0;
	क्रम (i = 0; i < 4096; i++) अणु
		cpu_set_t set;
		CPU_ZERO(&set);
		CPU_SET(i, &set);
		अगर (sched_setaffinity(getpid(), माप(set), &set) == 0) अणु
			अगर (i < *first)
				*first = i;
			अगर (i > *last)
				*last = i;
		पूर्ण
	पूर्ण
पूर्ण

/* Opencoded version क्रम fast mode */
अटल अंतरभूत पूर्णांक vringh_get_head(काष्ठा vringh *vrh, u16 *head)
अणु
	u16 avail_idx, i;
	पूर्णांक err;

	err = get_user(avail_idx, &vrh->vring.avail->idx);
	अगर (err)
		वापस err;

	अगर (vrh->last_avail_idx == avail_idx)
		वापस 0;

	/* Only get avail ring entries after they have been exposed by guest. */
	virtio_rmb(vrh->weak_barriers);

	i = vrh->last_avail_idx & (vrh->vring.num - 1);

	err = get_user(*head, &vrh->vring.avail->ring[i]);
	अगर (err)
		वापस err;

	vrh->last_avail_idx++;
	वापस 1;
पूर्ण

अटल पूर्णांक parallel_test(u64 features,
			 bool (*getrange)(काष्ठा vringh *vrh,
					  u64 addr, काष्ठा vringh_range *r),
			 bool fast_vringh)
अणु
	व्योम *host_map, *guest_map;
	पूर्णांक fd, mapsize, to_guest[2], to_host[2];
	अचिन्हित दीर्घ xfers = 0, notअगरies = 0, receives = 0;
	अचिन्हित पूर्णांक first_cpu, last_cpu;
	cpu_set_t cpu_set;
	अक्षर buf[128];

	/* Create real file to mmap. */
	fd = खोलो("/tmp/vringh_test-file", O_RDWR|O_CREAT|O_TRUNC, 0600);
	अगर (fd < 0)
		err(1, "Opening /tmp/vringh_test-file");

	/* Extra room at the end क्रम some data, and indirects */
	mapsize = vring_size(RINGSIZE, ALIGN)
		+ RINGSIZE * 2 * माप(पूर्णांक)
		+ RINGSIZE * 6 * माप(काष्ठा vring_desc);
	mapsize = (mapsize + getpagesize() - 1) & ~(getpagesize() - 1);
	ftruncate(fd, mapsize);

	/* Parent and child use separate addresses, to check our mapping logic! */
	host_map = mmap(शून्य, mapsize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	guest_map = mmap(शून्य, mapsize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	pipe(to_guest);
	pipe(to_host);

	CPU_ZERO(&cpu_set);
	find_cpus(&first_cpu, &last_cpu);
	म_लिखो("Using CPUS %u and %u\n", first_cpu, last_cpu);
	ख_साफ(मानक_निकास);

	अगर (विभाजन() != 0) अणु
		काष्ठा vringh vrh;
		पूर्णांक status, err, rlen = 0;
		अक्षर rbuf[5];

		/* We are the host: never access guest addresses! */
		munmap(guest_map, mapsize);

		__user_addr_min = host_map;
		__user_addr_max = __user_addr_min + mapsize;
		user_addr_offset = host_map - guest_map;
		निश्चित(user_addr_offset);

		बंद(to_guest[0]);
		बंद(to_host[1]);

		vring_init(&vrh.vring, RINGSIZE, host_map, ALIGN);
		vringh_init_user(&vrh, features, RINGSIZE, true,
				 vrh.vring.desc, vrh.vring.avail, vrh.vring.used);
		CPU_SET(first_cpu, &cpu_set);
		अगर (sched_setaffinity(getpid(), माप(cpu_set), &cpu_set))
			errx(1, "Could not set affinity to cpu %u", first_cpu);

		जबतक (xfers < NUM_XFERS) अणु
			काष्ठा iovec host_riov[2], host_wiov[2];
			काष्ठा vringh_iov riov, wiov;
			u16 head, written;

			अगर (fast_vringh) अणु
				क्रम (;;) अणु
					err = vringh_get_head(&vrh, &head);
					अगर (err != 0)
						अवरोध;
					err = vringh_need_notअगरy_user(&vrh);
					अगर (err < 0)
						errx(1, "vringh_need_notify_user: %i",
						     err);
					अगर (err) अणु
						ग_लिखो(to_guest[1], "", 1);
						notअगरies++;
					पूर्ण
				पूर्ण
				अगर (err != 1)
					errx(1, "vringh_get_head");
				written = 0;
				जाओ complete;
			पूर्ण अन्यथा अणु
				vringh_iov_init(&riov,
						host_riov,
						ARRAY_SIZE(host_riov));
				vringh_iov_init(&wiov,
						host_wiov,
						ARRAY_SIZE(host_wiov));

				err = vringh_getdesc_user(&vrh, &riov, &wiov,
							  getrange, &head);
			पूर्ण
			अगर (err == 0) अणु
				err = vringh_need_notअगरy_user(&vrh);
				अगर (err < 0)
					errx(1, "vringh_need_notify_user: %i",
					     err);
				अगर (err) अणु
					ग_लिखो(to_guest[1], "", 1);
					notअगरies++;
				पूर्ण

				अगर (!vringh_notअगरy_enable_user(&vrh))
					जारी;

				/* Swallow all notअगरies at once. */
				अगर (पढ़ो(to_host[0], buf, माप(buf)) < 1)
					अवरोध;

				vringh_notअगरy_disable_user(&vrh);
				receives++;
				जारी;
			पूर्ण
			अगर (err != 1)
				errx(1, "vringh_getdesc_user: %i", err);

			/* We simply copy bytes. */
			अगर (riov.used) अणु
				rlen = vringh_iov_pull_user(&riov, rbuf,
							    माप(rbuf));
				अगर (rlen != 4)
					errx(1, "vringh_iov_pull_user: %i",
					     rlen);
				निश्चित(riov.i == riov.used);
				written = 0;
			पूर्ण अन्यथा अणु
				err = vringh_iov_push_user(&wiov, rbuf, rlen);
				अगर (err != rlen)
					errx(1, "vringh_iov_push_user: %i",
					     err);
				निश्चित(wiov.i == wiov.used);
				written = err;
			पूर्ण
		complete:
			xfers++;

			err = vringh_complete_user(&vrh, head, written);
			अगर (err != 0)
				errx(1, "vringh_complete_user: %i", err);
		पूर्ण

		err = vringh_need_notअगरy_user(&vrh);
		अगर (err < 0)
			errx(1, "vringh_need_notify_user: %i", err);
		अगर (err) अणु
			ग_लिखो(to_guest[1], "", 1);
			notअगरies++;
		पूर्ण
		रुको(&status);
		अगर (!WIFEXITED(status))
			errx(1, "Child died with signal %i?", WTERMSIG(status));
		अगर (WEXITSTATUS(status) != 0)
			errx(1, "Child exited %i?", WEXITSTATUS(status));
		म_लिखो("Host: notified %lu, pinged %lu\n", notअगरies, receives);
		वापस 0;
	पूर्ण अन्यथा अणु
		काष्ठा guest_virtio_device gvdev;
		काष्ठा virtqueue *vq;
		अचिन्हित पूर्णांक *data;
		काष्ठा vring_desc *indirects;
		अचिन्हित पूर्णांक finished = 0;

		/* We pass sg[]s poपूर्णांकing पूर्णांकo here, but we need RINGSIZE+1 */
		data = guest_map + vring_size(RINGSIZE, ALIGN);
		indirects = (व्योम *)data + (RINGSIZE + 1) * 2 * माप(पूर्णांक);

		/* We are the guest. */
		munmap(host_map, mapsize);

		बंद(to_guest[1]);
		बंद(to_host[0]);

		gvdev.vdev.features = features;
		INIT_LIST_HEAD(&gvdev.vdev.vqs);
		gvdev.to_host_fd = to_host[1];
		gvdev.notअगरies = 0;

		CPU_SET(first_cpu, &cpu_set);
		अगर (sched_setaffinity(getpid(), माप(cpu_set), &cpu_set))
			err(1, "Could not set affinity to cpu %u", first_cpu);

		vq = vring_new_virtqueue(0, RINGSIZE, ALIGN, &gvdev.vdev, true,
					 false, guest_map,
					 fast_vringh ? no_notअगरy_host
					 : parallel_notअगरy_host,
					 never_callback_guest, "guest vq");

		/* Don't kमुक्त indirects. */
		__kमुक्त_ignore_start = indirects;
		__kमुक्त_ignore_end = indirects + RINGSIZE * 6;

		जबतक (xfers < NUM_XFERS) अणु
			काष्ठा scatterlist sg[4];
			अचिन्हित पूर्णांक num_sg, len;
			पूर्णांक *dbuf, err;
			bool output = !(xfers % 2);

			/* Consume bufs. */
			जबतक ((dbuf = virtqueue_get_buf(vq, &len)) != शून्य) अणु
				अगर (len == 4)
					निश्चित(*dbuf == finished - 1);
				अन्यथा अगर (!fast_vringh)
					निश्चित(*dbuf == finished);
				finished++;
			पूर्ण

			/* Produce a buffer. */
			dbuf = data + (xfers % (RINGSIZE + 1));

			अगर (output)
				*dbuf = xfers;
			अन्यथा
				*dbuf = -1;

			चयन ((xfers / माप(*dbuf)) % 4) अणु
			हाल 0:
				/* Nasty three-element sg list. */
				sg_init_table(sg, num_sg = 3);
				sg_set_buf(&sg[0], (व्योम *)dbuf, 1);
				sg_set_buf(&sg[1], (व्योम *)dbuf + 1, 2);
				sg_set_buf(&sg[2], (व्योम *)dbuf + 3, 1);
				अवरोध;
			हाल 1:
				sg_init_table(sg, num_sg = 2);
				sg_set_buf(&sg[0], (व्योम *)dbuf, 1);
				sg_set_buf(&sg[1], (व्योम *)dbuf + 1, 3);
				अवरोध;
			हाल 2:
				sg_init_table(sg, num_sg = 1);
				sg_set_buf(&sg[0], (व्योम *)dbuf, 4);
				अवरोध;
			हाल 3:
				sg_init_table(sg, num_sg = 4);
				sg_set_buf(&sg[0], (व्योम *)dbuf, 1);
				sg_set_buf(&sg[1], (व्योम *)dbuf + 1, 1);
				sg_set_buf(&sg[2], (व्योम *)dbuf + 2, 1);
				sg_set_buf(&sg[3], (व्योम *)dbuf + 3, 1);
				अवरोध;
			पूर्ण

			/* May allocate an indirect, so क्रमce it to allocate
			 * user addr */
			__kदो_स्मृति_fake = indirects + (xfers % RINGSIZE) * 4;
			अगर (output)
				err = virtqueue_add_outbuf(vq, sg, num_sg, dbuf,
							   GFP_KERNEL);
			अन्यथा
				err = virtqueue_add_inbuf(vq, sg, num_sg,
							  dbuf, GFP_KERNEL);

			अगर (err == -ENOSPC) अणु
				अगर (!virtqueue_enable_cb_delayed(vq))
					जारी;
				/* Swallow all notअगरies at once. */
				अगर (पढ़ो(to_guest[0], buf, माप(buf)) < 1)
					अवरोध;
				
				receives++;
				virtqueue_disable_cb(vq);
				जारी;
			पूर्ण

			अगर (err)
				errx(1, "virtqueue_add_in/outbuf: %i", err);

			xfers++;
			virtqueue_kick(vq);
		पूर्ण

		/* Any extra? */
		जबतक (finished != xfers) अणु
			पूर्णांक *dbuf;
			अचिन्हित पूर्णांक len;

			/* Consume bufs. */
			dbuf = virtqueue_get_buf(vq, &len);
			अगर (dbuf) अणु
				अगर (len == 4)
					निश्चित(*dbuf == finished - 1);
				अन्यथा
					निश्चित(len == 0);
				finished++;
				जारी;
			पूर्ण

			अगर (!virtqueue_enable_cb_delayed(vq))
				जारी;
			अगर (पढ़ो(to_guest[0], buf, माप(buf)) < 1)
				अवरोध;
				
			receives++;
			virtqueue_disable_cb(vq);
		पूर्ण

		म_लिखो("Guest: notified %lu, pinged %lu\n",
		       gvdev.notअगरies, receives);
		vring_del_virtqueue(vq);
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	काष्ठा virtio_device vdev;
	काष्ठा virtqueue *vq;
	काष्ठा vringh vrh;
	काष्ठा scatterlist guest_sg[RINGSIZE], *sgs[2];
	काष्ठा iovec host_riov[2], host_wiov[2];
	काष्ठा vringh_iov riov, wiov;
	काष्ठा vring_used_elem used[RINGSIZE];
	अक्षर buf[28];
	u16 head;
	पूर्णांक err;
	अचिन्हित i;
	व्योम *ret;
	bool (*getrange)(काष्ठा vringh *vrh, u64 addr, काष्ठा vringh_range *r);
	bool fast_vringh = false, parallel = false;

	getrange = getrange_iov;
	vdev.features = 0;
	INIT_LIST_HEAD(&vdev.vqs);

	जबतक (argv[1]) अणु
		अगर (म_भेद(argv[1], "--indirect") == 0)
			__virtio_set_bit(&vdev, VIRTIO_RING_F_INसूचीECT_DESC);
		अन्यथा अगर (म_भेद(argv[1], "--eventidx") == 0)
			__virtio_set_bit(&vdev, VIRTIO_RING_F_EVENT_IDX);
		अन्यथा अगर (म_भेद(argv[1], "--virtio-1") == 0)
			__virtio_set_bit(&vdev, VIRTIO_F_VERSION_1);
		अन्यथा अगर (म_भेद(argv[1], "--slow-range") == 0)
			getrange = getrange_slow;
		अन्यथा अगर (म_भेद(argv[1], "--fast-vringh") == 0)
			fast_vringh = true;
		अन्यथा अगर (म_भेद(argv[1], "--parallel") == 0)
			parallel = true;
		अन्यथा
			errx(1, "Unknown arg %s", argv[1]);
		argv++;
	पूर्ण

	अगर (parallel)
		वापस parallel_test(vdev.features, getrange, fast_vringh);

	अगर (posix_memalign(&__user_addr_min, PAGE_SIZE, USER_MEM) != 0)
		पात();
	__user_addr_max = __user_addr_min + USER_MEM;
	स_रखो(__user_addr_min, 0, vring_size(RINGSIZE, ALIGN));

	/* Set up guest side. */
	vq = vring_new_virtqueue(0, RINGSIZE, ALIGN, &vdev, true, false,
				 __user_addr_min,
				 never_notअगरy_host, never_callback_guest,
				 "guest vq");

	/* Set up host side. */
	vring_init(&vrh.vring, RINGSIZE, __user_addr_min, ALIGN);
	vringh_init_user(&vrh, vdev.features, RINGSIZE, true,
			 vrh.vring.desc, vrh.vring.avail, vrh.vring.used);

	/* No descriptor to get yet... */
	err = vringh_getdesc_user(&vrh, &riov, &wiov, getrange, &head);
	अगर (err != 0)
		errx(1, "vringh_getdesc_user: %i", err);

	/* Guest माला_दो in a descriptor. */
	स_नकल(__user_addr_max - 1, "a", 1);
	sg_init_table(guest_sg, 1);
	sg_set_buf(&guest_sg[0], __user_addr_max - 1, 1);
	sg_init_table(guest_sg+1, 1);
	sg_set_buf(&guest_sg[1], __user_addr_max - 3, 2);
	sgs[0] = &guest_sg[0];
	sgs[1] = &guest_sg[1];

	/* May allocate an indirect, so क्रमce it to allocate user addr */
	__kदो_स्मृति_fake = __user_addr_min + vring_size(RINGSIZE, ALIGN);
	err = virtqueue_add_sgs(vq, sgs, 1, 1, &err, GFP_KERNEL);
	अगर (err)
		errx(1, "virtqueue_add_sgs: %i", err);
	__kदो_स्मृति_fake = शून्य;

	/* Host retreives it. */
	vringh_iov_init(&riov, host_riov, ARRAY_SIZE(host_riov));
	vringh_iov_init(&wiov, host_wiov, ARRAY_SIZE(host_wiov));

	err = vringh_getdesc_user(&vrh, &riov, &wiov, getrange, &head);
	अगर (err != 1)
		errx(1, "vringh_getdesc_user: %i", err);

	निश्चित(riov.used == 1);
	निश्चित(riov.iov[0].iov_base == __user_addr_max - 1);
	निश्चित(riov.iov[0].iov_len == 1);
	अगर (getrange != getrange_slow) अणु
		निश्चित(wiov.used == 1);
		निश्चित(wiov.iov[0].iov_base == __user_addr_max - 3);
		निश्चित(wiov.iov[0].iov_len == 2);
	पूर्ण अन्यथा अणु
		निश्चित(wiov.used == 2);
		निश्चित(wiov.iov[0].iov_base == __user_addr_max - 3);
		निश्चित(wiov.iov[0].iov_len == 1);
		निश्चित(wiov.iov[1].iov_base == __user_addr_max - 2);
		निश्चित(wiov.iov[1].iov_len == 1);
	पूर्ण

	err = vringh_iov_pull_user(&riov, buf, 5);
	अगर (err != 1)
		errx(1, "vringh_iov_pull_user: %i", err);
	निश्चित(buf[0] == 'a');
	निश्चित(riov.i == 1);
	निश्चित(vringh_iov_pull_user(&riov, buf, 5) == 0);

	स_नकल(buf, "bcdef", 5);
	err = vringh_iov_push_user(&wiov, buf, 5);
	अगर (err != 2)
		errx(1, "vringh_iov_push_user: %i", err);
	निश्चित(स_भेद(__user_addr_max - 3, "bc", 2) == 0);
	निश्चित(wiov.i == wiov.used);
	निश्चित(vringh_iov_push_user(&wiov, buf, 5) == 0);

	/* Host is करोne. */
	err = vringh_complete_user(&vrh, head, err);
	अगर (err != 0)
		errx(1, "vringh_complete_user: %i", err);

	/* Guest should see used token now. */
	__kमुक्त_ignore_start = __user_addr_min + vring_size(RINGSIZE, ALIGN);
	__kमुक्त_ignore_end = __kमुक्त_ignore_start + 1;
	ret = virtqueue_get_buf(vq, &i);
	अगर (ret != &err)
		errx(1, "virtqueue_get_buf: %p", ret);
	निश्चित(i == 2);

	/* Guest माला_दो in a huge descriptor. */
	sg_init_table(guest_sg, RINGSIZE);
	क्रम (i = 0; i < RINGSIZE; i++) अणु
		sg_set_buf(&guest_sg[i],
			   __user_addr_max - USER_MEM/4, USER_MEM/4);
	पूर्ण

	/* Fill contents with recognisable garbage. */
	क्रम (i = 0; i < USER_MEM/4; i++)
		((अक्षर *)__user_addr_max - USER_MEM/4)[i] = i;

	/* This will allocate an indirect, so क्रमce it to allocate user addr */
	__kदो_स्मृति_fake = __user_addr_min + vring_size(RINGSIZE, ALIGN);
	err = virtqueue_add_outbuf(vq, guest_sg, RINGSIZE, &err, GFP_KERNEL);
	अगर (err)
		errx(1, "virtqueue_add_outbuf (large): %i", err);
	__kदो_स्मृति_fake = शून्य;

	/* Host picks it up (allocates new iov). */
	vringh_iov_init(&riov, host_riov, ARRAY_SIZE(host_riov));
	vringh_iov_init(&wiov, host_wiov, ARRAY_SIZE(host_wiov));

	err = vringh_getdesc_user(&vrh, &riov, &wiov, getrange, &head);
	अगर (err != 1)
		errx(1, "vringh_getdesc_user: %i", err);

	निश्चित(riov.max_num & VRINGH_IOV_ALLOCATED);
	निश्चित(riov.iov != host_riov);
	अगर (getrange != getrange_slow)
		निश्चित(riov.used == RINGSIZE);
	अन्यथा
		निश्चित(riov.used == RINGSIZE * USER_MEM/4);

	निश्चित(!(wiov.max_num & VRINGH_IOV_ALLOCATED));
	निश्चित(wiov.used == 0);

	/* Pull data back out (in odd chunks), should be as expected. */
	क्रम (i = 0; i < RINGSIZE * USER_MEM/4; i += 3) अणु
		err = vringh_iov_pull_user(&riov, buf, 3);
		अगर (err != 3 && i + err != RINGSIZE * USER_MEM/4)
			errx(1, "vringh_iov_pull_user large: %i", err);
		निश्चित(buf[0] == (अक्षर)i);
		निश्चित(err < 2 || buf[1] == (अक्षर)(i + 1));
		निश्चित(err < 3 || buf[2] == (अक्षर)(i + 2));
	पूर्ण
	निश्चित(riov.i == riov.used);
	vringh_iov_cleanup(&riov);
	vringh_iov_cleanup(&wiov);

	/* Complete using multi पूर्णांकerface, just because we can. */
	used[0].id = head;
	used[0].len = 0;
	err = vringh_complete_multi_user(&vrh, used, 1);
	अगर (err)
		errx(1, "vringh_complete_multi_user(1): %i", err);

	/* Free up those descriptors. */
	ret = virtqueue_get_buf(vq, &i);
	अगर (ret != &err)
		errx(1, "virtqueue_get_buf: %p", ret);

	/* Add lots of descriptors. */
	sg_init_table(guest_sg, 1);
	sg_set_buf(&guest_sg[0], __user_addr_max - 1, 1);
	क्रम (i = 0; i < RINGSIZE; i++) अणु
		err = virtqueue_add_outbuf(vq, guest_sg, 1, &err, GFP_KERNEL);
		अगर (err)
			errx(1, "virtqueue_add_outbuf (multiple): %i", err);
	पूर्ण

	/* Now get many, and consume them all at once. */
	vringh_iov_init(&riov, host_riov, ARRAY_SIZE(host_riov));
	vringh_iov_init(&wiov, host_wiov, ARRAY_SIZE(host_wiov));

	क्रम (i = 0; i < RINGSIZE; i++) अणु
		err = vringh_getdesc_user(&vrh, &riov, &wiov, getrange, &head);
		अगर (err != 1)
			errx(1, "vringh_getdesc_user: %i", err);
		used[i].id = head;
		used[i].len = 0;
	पूर्ण
	/* Make sure it wraps around ring, to test! */
	निश्चित(vrh.vring.used->idx % RINGSIZE != 0);
	err = vringh_complete_multi_user(&vrh, used, RINGSIZE);
	अगर (err)
		errx(1, "vringh_complete_multi_user: %i", err);

	/* Free those buffers. */
	क्रम (i = 0; i < RINGSIZE; i++) अणु
		अचिन्हित len;
		निश्चित(virtqueue_get_buf(vq, &len) != शून्य);
	पूर्ण

	/* Test weird (but legal!) indirect. */
	अगर (__virtio_test_bit(&vdev, VIRTIO_RING_F_INसूचीECT_DESC)) अणु
		अक्षर *data = __user_addr_max - USER_MEM/4;
		काष्ठा vring_desc *d = __user_addr_max - USER_MEM/2;
		काष्ठा vring vring;

		/* Force creation of direct, which we modअगरy. */
		__virtio_clear_bit(&vdev, VIRTIO_RING_F_INसूचीECT_DESC);
		vq = vring_new_virtqueue(0, RINGSIZE, ALIGN, &vdev, true,
					 false, __user_addr_min,
					 never_notअगरy_host,
					 never_callback_guest,
					 "guest vq");

		sg_init_table(guest_sg, 4);
		sg_set_buf(&guest_sg[0], d, माप(*d)*2);
		sg_set_buf(&guest_sg[1], d + 2, माप(*d)*1);
		sg_set_buf(&guest_sg[2], data + 6, 4);
		sg_set_buf(&guest_sg[3], d + 3, माप(*d)*3);

		err = virtqueue_add_outbuf(vq, guest_sg, 4, &err, GFP_KERNEL);
		अगर (err)
			errx(1, "virtqueue_add_outbuf (indirect): %i", err);

		vring_init(&vring, RINGSIZE, __user_addr_min, ALIGN);

		/* They're used in order, but द्विगुन-check... */
		निश्चित(vring.desc[0].addr == (अचिन्हित दीर्घ)d);
		निश्चित(vring.desc[1].addr == (अचिन्हित दीर्घ)(d+2));
		निश्चित(vring.desc[2].addr == (अचिन्हित दीर्घ)data + 6);
		निश्चित(vring.desc[3].addr == (अचिन्हित दीर्घ)(d+3));
		vring.desc[0].flags |= VRING_DESC_F_INसूचीECT;
		vring.desc[1].flags |= VRING_DESC_F_INसूचीECT;
		vring.desc[3].flags |= VRING_DESC_F_INसूचीECT;

		/* First indirect */
		d[0].addr = (अचिन्हित दीर्घ)data;
		d[0].len = 1;
		d[0].flags = VRING_DESC_F_NEXT;
		d[0].next = 1;
		d[1].addr = (अचिन्हित दीर्घ)data + 1;
		d[1].len = 2;
		d[1].flags = 0;

		/* Second indirect */
		d[2].addr = (अचिन्हित दीर्घ)data + 3;
		d[2].len = 3;
		d[2].flags = 0;

		/* Third indirect */
		d[3].addr = (अचिन्हित दीर्घ)data + 10;
		d[3].len = 5;
		d[3].flags = VRING_DESC_F_NEXT;
		d[3].next = 1;
		d[4].addr = (अचिन्हित दीर्घ)data + 15;
		d[4].len = 6;
		d[4].flags = VRING_DESC_F_NEXT;
		d[4].next = 2;
		d[5].addr = (अचिन्हित दीर्घ)data + 21;
		d[5].len = 7;
		d[5].flags = 0;

		/* Host picks it up (allocates new iov). */
		vringh_iov_init(&riov, host_riov, ARRAY_SIZE(host_riov));
		vringh_iov_init(&wiov, host_wiov, ARRAY_SIZE(host_wiov));

		err = vringh_getdesc_user(&vrh, &riov, &wiov, getrange, &head);
		अगर (err != 1)
			errx(1, "vringh_getdesc_user: %i", err);

		अगर (head != 0)
			errx(1, "vringh_getdesc_user: head %i not 0", head);

		निश्चित(riov.max_num & VRINGH_IOV_ALLOCATED);
		अगर (getrange != getrange_slow)
			निश्चित(riov.used == 7);
		अन्यथा
			निश्चित(riov.used == 28);
		err = vringh_iov_pull_user(&riov, buf, 29);
		निश्चित(err == 28);

		/* Data should be linear. */
		क्रम (i = 0; i < err; i++)
			निश्चित(buf[i] == i);
		vringh_iov_cleanup(&riov);
	पूर्ण

	/* Don't leak memory... */
	vring_del_virtqueue(vq);
	मुक्त(__user_addr_min);

	वापस 0;
पूर्ण
