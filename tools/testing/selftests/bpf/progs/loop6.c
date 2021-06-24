<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/ptrace.h>
#समावेश <मानकघोष.स>
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>
#समावेश <bpf/bpf_tracing.h>

अक्षर _license[] SEC("license") = "GPL";

/* typically virtio scsi has max SGs of 6 */
#घोषणा VIRTIO_MAX_SGS	6

/* Verअगरier will fail with SG_MAX = 128. The failure can be
 * workarounded with a smaller SG_MAX, e.g. 10.
 */
#घोषणा WORKAROUND
#अगर_घोषित WORKAROUND
#घोषणा SG_MAX		10
#अन्यथा
/* typically virtio blk has max SEG of 128 */
#घोषणा SG_MAX		128
#पूर्ण_अगर

#घोषणा SG_CHAIN	0x01UL
#घोषणा SG_END		0x02UL

काष्ठा scatterlist अणु
	अचिन्हित दीर्घ   page_link;
	अचिन्हित पूर्णांक    offset;
	अचिन्हित पूर्णांक    length;
पूर्ण;

#घोषणा sg_is_chain(sg)		((sg)->page_link & SG_CHAIN)
#घोषणा sg_is_last(sg)		((sg)->page_link & SG_END)
#घोषणा sg_chain_ptr(sg)	\
	((काष्ठा scatterlist *) ((sg)->page_link & ~(SG_CHAIN | SG_END)))

अटल अंतरभूत काष्ठा scatterlist *__sg_next(काष्ठा scatterlist *sgp)
अणु
	काष्ठा scatterlist sg;

	bpf_probe_पढ़ो_kernel(&sg, माप(sg), sgp);
	अगर (sg_is_last(&sg))
		वापस शून्य;

	sgp++;

	bpf_probe_पढ़ो_kernel(&sg, माप(sg), sgp);
	अगर (sg_is_chain(&sg))
		sgp = sg_chain_ptr(&sg);

	वापस sgp;
पूर्ण

अटल अंतरभूत काष्ठा scatterlist *get_sgp(काष्ठा scatterlist **sgs, पूर्णांक i)
अणु
	काष्ठा scatterlist *sgp;

	bpf_probe_पढ़ो_kernel(&sgp, माप(sgp), sgs + i);
	वापस sgp;
पूर्ण

पूर्णांक config = 0;
पूर्णांक result = 0;

SEC("kprobe/virtqueue_add_sgs")
पूर्णांक BPF_KPROBE(trace_virtqueue_add_sgs, व्योम *unused, काष्ठा scatterlist **sgs,
	       अचिन्हित पूर्णांक out_sgs, अचिन्हित पूर्णांक in_sgs)
अणु
	काष्ठा scatterlist *sgp = शून्य;
	__u64 length1 = 0, length2 = 0;
	अचिन्हित पूर्णांक i, n, len;

	अगर (config != 0)
		वापस 0;

	क्रम (i = 0; (i < VIRTIO_MAX_SGS) && (i < out_sgs); i++) अणु
		क्रम (n = 0, sgp = get_sgp(sgs, i); sgp && (n < SG_MAX);
		     sgp = __sg_next(sgp)) अणु
			bpf_probe_पढ़ो_kernel(&len, माप(len), &sgp->length);
			length1 += len;
			n++;
		पूर्ण
	पूर्ण

	क्रम (i = 0; (i < VIRTIO_MAX_SGS) && (i < in_sgs); i++) अणु
		क्रम (n = 0, sgp = get_sgp(sgs, i); sgp && (n < SG_MAX);
		     sgp = __sg_next(sgp)) अणु
			bpf_probe_पढ़ो_kernel(&len, माप(len), &sgp->length);
			length2 += len;
			n++;
		पूर्ण
	पूर्ण

	config = 1;
	result = length2 - length1;
	वापस 0;
पूर्ण
