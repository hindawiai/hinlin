<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <getopt.h>
#समावेश <सीमा.स>
#समावेश <माला.स>
#समावेश <poll.h>
#समावेश <sys/eventfd.h>
#समावेश <मानककोष.स>
#समावेश <निश्चित.स>
#समावेश <unistd.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <fcntl.h>
#समावेश <stdbool.h>
#समावेश <linux/virtio_types.h>
#समावेश <linux/vhost.h>
#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_ring.h>
#समावेश "../../drivers/vhost/test.h"

#घोषणा RANDOM_BATCH -1

/* Unused */
व्योम *__kदो_स्मृति_fake, *__kमुक्त_ignore_start, *__kमुक्त_ignore_end;

काष्ठा vq_info अणु
	पूर्णांक kick;
	पूर्णांक call;
	पूर्णांक num;
	पूर्णांक idx;
	व्योम *ring;
	/* copy used क्रम control */
	काष्ठा vring vring;
	काष्ठा virtqueue *vq;
पूर्ण;

काष्ठा vdev_info अणु
	काष्ठा virtio_device vdev;
	पूर्णांक control;
	काष्ठा pollfd fds[1];
	काष्ठा vq_info vqs[1];
	पूर्णांक nvqs;
	व्योम *buf;
	माप_प्रकार buf_size;
	काष्ठा vhost_memory *mem;
पूर्ण;

अटल स्थिर काष्ठा vhost_vring_file no_backend = अणु .fd = -1 पूर्ण,
				     backend = अणु .fd = 1 पूर्ण;
अटल स्थिर काष्ठा vhost_vring_state null_state = अणुपूर्ण;

bool vq_notअगरy(काष्ठा virtqueue *vq)
अणु
	काष्ठा vq_info *info = vq->priv;
	अचिन्हित दीर्घ दीर्घ v = 1;
	पूर्णांक r;
	r = ग_लिखो(info->kick, &v, माप v);
	निश्चित(r == माप v);
	वापस true;
पूर्ण

व्योम vq_callback(काष्ठा virtqueue *vq)
अणु
पूर्ण


व्योम vhost_vq_setup(काष्ठा vdev_info *dev, काष्ठा vq_info *info)
अणु
	काष्ठा vhost_vring_state state = अणु .index = info->idx पूर्ण;
	काष्ठा vhost_vring_file file = अणु .index = info->idx पूर्ण;
	अचिन्हित दीर्घ दीर्घ features = dev->vdev.features;
	काष्ठा vhost_vring_addr addr = अणु
		.index = info->idx,
		.desc_user_addr = (uपूर्णांक64_t)(अचिन्हित दीर्घ)info->vring.desc,
		.avail_user_addr = (uपूर्णांक64_t)(अचिन्हित दीर्घ)info->vring.avail,
		.used_user_addr = (uपूर्णांक64_t)(अचिन्हित दीर्घ)info->vring.used,
	पूर्ण;
	पूर्णांक r;
	r = ioctl(dev->control, VHOST_SET_FEATURES, &features);
	निश्चित(r >= 0);
	state.num = info->vring.num;
	r = ioctl(dev->control, VHOST_SET_VRING_NUM, &state);
	निश्चित(r >= 0);
	state.num = 0;
	r = ioctl(dev->control, VHOST_SET_VRING_BASE, &state);
	निश्चित(r >= 0);
	r = ioctl(dev->control, VHOST_SET_VRING_ADDR, &addr);
	निश्चित(r >= 0);
	file.fd = info->kick;
	r = ioctl(dev->control, VHOST_SET_VRING_KICK, &file);
	निश्चित(r >= 0);
	file.fd = info->call;
	r = ioctl(dev->control, VHOST_SET_VRING_CALL, &file);
	निश्चित(r >= 0);
पूर्ण

अटल व्योम vq_reset(काष्ठा vq_info *info, पूर्णांक num, काष्ठा virtio_device *vdev)
अणु
	अगर (info->vq)
		vring_del_virtqueue(info->vq);

	स_रखो(info->ring, 0, vring_size(num, 4096));
	vring_init(&info->vring, num, info->ring, 4096);
	info->vq = __vring_new_virtqueue(info->idx, info->vring, vdev, true,
					 false, vq_notअगरy, vq_callback, "test");
	निश्चित(info->vq);
	info->vq->priv = info;
पूर्ण

अटल व्योम vq_info_add(काष्ठा vdev_info *dev, पूर्णांक num)
अणु
	काष्ठा vq_info *info = &dev->vqs[dev->nvqs];
	पूर्णांक r;
	info->idx = dev->nvqs;
	info->kick = eventfd(0, EFD_NONBLOCK);
	info->call = eventfd(0, EFD_NONBLOCK);
	r = posix_memalign(&info->ring, 4096, vring_size(num, 4096));
	निश्चित(r >= 0);
	vq_reset(info, num, &dev->vdev);
	vhost_vq_setup(dev, info);
	dev->fds[info->idx].fd = info->call;
	dev->fds[info->idx].events = POLLIN;
	dev->nvqs++;
पूर्ण

अटल व्योम vdev_info_init(काष्ठा vdev_info* dev, अचिन्हित दीर्घ दीर्घ features)
अणु
	पूर्णांक r;
	स_रखो(dev, 0, माप *dev);
	dev->vdev.features = features;
	INIT_LIST_HEAD(&dev->vdev.vqs);
	dev->buf_size = 1024;
	dev->buf = दो_स्मृति(dev->buf_size);
	निश्चित(dev->buf);
        dev->control = खोलो("/dev/vhost-test", O_RDWR);
	निश्चित(dev->control >= 0);
	r = ioctl(dev->control, VHOST_SET_OWNER, शून्य);
	निश्चित(r >= 0);
	dev->mem = दो_स्मृति(दुरत्व(काष्ठा vhost_memory, regions) +
			  माप dev->mem->regions[0]);
	निश्चित(dev->mem);
	स_रखो(dev->mem, 0, दुरत्व(काष्ठा vhost_memory, regions) +
                          माप dev->mem->regions[0]);
	dev->mem->nregions = 1;
	dev->mem->regions[0].guest_phys_addr = (दीर्घ)dev->buf;
	dev->mem->regions[0].userspace_addr = (दीर्घ)dev->buf;
	dev->mem->regions[0].memory_size = dev->buf_size;
	r = ioctl(dev->control, VHOST_SET_MEM_TABLE, dev->mem);
	निश्चित(r >= 0);
पूर्ण

/* TODO: this is pretty bad: we get a cache line bounce
 * क्रम the रुको queue on poll and another one on पढ़ो,
 * plus the पढ़ो which is there just to clear the
 * current state. */
अटल व्योम रुको_क्रम_पूर्णांकerrupt(काष्ठा vdev_info *dev)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ दीर्घ val;
	poll(dev->fds, dev->nvqs, -1);
	क्रम (i = 0; i < dev->nvqs; ++i)
		अगर (dev->fds[i].revents & POLLIN) अणु
			पढ़ो(dev->fds[i].fd, &val, माप val);
		पूर्ण
पूर्ण

अटल व्योम run_test(काष्ठा vdev_info *dev, काष्ठा vq_info *vq,
		     bool delayed, पूर्णांक batch, पूर्णांक reset_n, पूर्णांक bufs)
अणु
	काष्ठा scatterlist sl;
	दीर्घ started = 0, completed = 0, next_reset = reset_n;
	दीर्घ completed_beक्रमe, started_beक्रमe;
	पूर्णांक r, test = 1;
	अचिन्हित len;
	दीर्घ दीर्घ spurious = 0;
	स्थिर bool अक्रमom_batch = batch == RANDOM_BATCH;

	r = ioctl(dev->control, VHOST_TEST_RUN, &test);
	निश्चित(r >= 0);
	अगर (!reset_n) अणु
		next_reset = पूर्णांक_उच्च;
	पूर्ण

	क्रम (;;) अणु
		virtqueue_disable_cb(vq->vq);
		completed_beक्रमe = completed;
		started_beक्रमe = started;
		करो अणु
			स्थिर bool reset = completed > next_reset;
			अगर (अक्रमom_batch)
				batch = (अक्रमom() % vq->vring.num) + 1;

			जबतक (started < bufs &&
			       (started - completed) < batch) अणु
				sg_init_one(&sl, dev->buf, dev->buf_size);
				r = virtqueue_add_outbuf(vq->vq, &sl, 1,
							 dev->buf + started,
							 GFP_ATOMIC);
				अगर (unlikely(r != 0)) अणु
					अगर (r == -ENOSPC &&
					    started > started_beक्रमe)
						r = 0;
					अन्यथा
						r = -1;
					अवरोध;
				पूर्ण

				++started;

				अगर (unlikely(!virtqueue_kick(vq->vq))) अणु
					r = -1;
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (started >= bufs)
				r = -1;

			अगर (reset) अणु
				r = ioctl(dev->control, VHOST_TEST_SET_BACKEND,
					  &no_backend);
				निश्चित(!r);
			पूर्ण

			/* Flush out completed bufs अगर any */
			जबतक (virtqueue_get_buf(vq->vq, &len)) अणु
				++completed;
				r = 0;
			पूर्ण

			अगर (reset) अणु
				काष्ठा vhost_vring_state s = अणु .index = 0 पूर्ण;

				vq_reset(vq, vq->vring.num, &dev->vdev);

				r = ioctl(dev->control, VHOST_GET_VRING_BASE,
					  &s);
				निश्चित(!r);

				s.num = 0;
				r = ioctl(dev->control, VHOST_SET_VRING_BASE,
					  &null_state);
				निश्चित(!r);

				r = ioctl(dev->control, VHOST_TEST_SET_BACKEND,
					  &backend);
				निश्चित(!r);

				started = completed;
				जबतक (completed > next_reset)
					next_reset += completed;
			पूर्ण
		पूर्ण जबतक (r == 0);
		अगर (completed == completed_beक्रमe && started == started_beक्रमe)
			++spurious;
		निश्चित(completed <= bufs);
		निश्चित(started <= bufs);
		अगर (completed == bufs)
			अवरोध;
		अगर (delayed) अणु
			अगर (virtqueue_enable_cb_delayed(vq->vq))
				रुको_क्रम_पूर्णांकerrupt(dev);
		पूर्ण अन्यथा अणु
			अगर (virtqueue_enable_cb(vq->vq))
				रुको_क्रम_पूर्णांकerrupt(dev);
		पूर्ण
	पूर्ण
	test = 0;
	r = ioctl(dev->control, VHOST_TEST_RUN, &test);
	निश्चित(r >= 0);
	ख_लिखो(मानक_त्रुटि,
		"spurious wakeups: 0x%llx started=0x%lx completed=0x%lx\n",
		spurious, started, completed);
पूर्ण

स्थिर अक्षर optstring[] = "h";
स्थिर काष्ठा option दीर्घopts[] = अणु
	अणु
		.name = "help",
		.val = 'h',
	पूर्ण,
	अणु
		.name = "event-idx",
		.val = 'E',
	पूर्ण,
	अणु
		.name = "no-event-idx",
		.val = 'e',
	पूर्ण,
	अणु
		.name = "indirect",
		.val = 'I',
	पूर्ण,
	अणु
		.name = "no-indirect",
		.val = 'i',
	पूर्ण,
	अणु
		.name = "virtio-1",
		.val = '1',
	पूर्ण,
	अणु
		.name = "no-virtio-1",
		.val = '0',
	पूर्ण,
	अणु
		.name = "delayed-interrupt",
		.val = 'D',
	पूर्ण,
	अणु
		.name = "no-delayed-interrupt",
		.val = 'd',
	पूर्ण,
	अणु
		.name = "batch",
		.val = 'b',
		.has_arg = required_argument,
	पूर्ण,
	अणु
		.name = "reset",
		.val = 'r',
		.has_arg = optional_argument,
	पूर्ण,
	अणु
	पूर्ण
पूर्ण;

अटल व्योम help(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "Usage: virtio_test [--help]"
		" [--no-indirect]"
		" [--no-event-idx]"
		" [--no-virtio-1]"
		" [--delayed-interrupt]"
		" [--batch=random/N]"
		" [--reset=N]"
		"\n");
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	काष्ठा vdev_info dev;
	अचिन्हित दीर्घ दीर्घ features = (1ULL << VIRTIO_RING_F_INसूचीECT_DESC) |
		(1ULL << VIRTIO_RING_F_EVENT_IDX) | (1ULL << VIRTIO_F_VERSION_1);
	दीर्घ batch = 1, reset = 0;
	पूर्णांक o;
	bool delayed = false;

	क्रम (;;) अणु
		o = getopt_दीर्घ(argc, argv, optstring, दीर्घopts, शून्य);
		चयन (o) अणु
		हाल -1:
			जाओ करोne;
		हाल '?':
			help();
			निकास(2);
		हाल 'e':
			features &= ~(1ULL << VIRTIO_RING_F_EVENT_IDX);
			अवरोध;
		हाल 'h':
			help();
			जाओ करोne;
		हाल 'i':
			features &= ~(1ULL << VIRTIO_RING_F_INसूचीECT_DESC);
			अवरोध;
		हाल '0':
			features &= ~(1ULL << VIRTIO_F_VERSION_1);
			अवरोध;
		हाल 'D':
			delayed = true;
			अवरोध;
		हाल 'b':
			अगर (0 == म_भेद(optarg, "random")) अणु
				batch = RANDOM_BATCH;
			पूर्ण अन्यथा अणु
				batch = म_से_दीर्घ(optarg, शून्य, 10);
				निश्चित(batch > 0);
				निश्चित(batch < (दीर्घ)पूर्णांक_उच्च + 1);
			पूर्ण
			अवरोध;
		हाल 'r':
			अगर (!optarg) अणु
				reset = 1;
			पूर्ण अन्यथा अणु
				reset = म_से_दीर्घ(optarg, शून्य, 10);
				निश्चित(reset > 0);
				निश्चित(reset < (दीर्घ)पूर्णांक_उच्च + 1);
			पूर्ण
			अवरोध;
		शेष:
			निश्चित(0);
			अवरोध;
		पूर्ण
	पूर्ण

करोne:
	vdev_info_init(&dev, features);
	vq_info_add(&dev, 256);
	run_test(&dev, &dev.vqs[0], delayed, batch, reset, 0x100000);
	वापस 0;
पूर्ण
