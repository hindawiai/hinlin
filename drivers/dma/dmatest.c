<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * DMA Engine test module
 *
 * Copyright (C) 2007 Aपंचांगel Corporation
 * Copyright (C) 2013 Intel Corporation
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/init.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>

अटल अचिन्हित पूर्णांक test_buf_size = 16384;
module_param(test_buf_size, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(test_buf_size, "Size of the memcpy test buffer");

अटल अक्षर test_device[32];
module_param_string(device, test_device, माप(test_device),
		S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(device, "Bus ID of the DMA Engine to test (default: any)");

अटल अचिन्हित पूर्णांक thपढ़ोs_per_chan = 1;
module_param(thपढ़ोs_per_chan, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(thपढ़ोs_per_chan,
		"Number of threads to start per channel (default: 1)");

अटल अचिन्हित पूर्णांक max_channels;
module_param(max_channels, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(max_channels,
		"Maximum number of channels to use (default: all)");

अटल अचिन्हित पूर्णांक iterations;
module_param(iterations, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(iterations,
		"Iterations before stopping test (default: infinite)");

अटल अचिन्हित पूर्णांक dmatest;
module_param(dmatest, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(dmatest,
		"dmatest 0-memcpy 1-memset (default: 0)");

अटल अचिन्हित पूर्णांक xor_sources = 3;
module_param(xor_sources, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(xor_sources,
		"Number of xor source buffers (default: 3)");

अटल अचिन्हित पूर्णांक pq_sources = 3;
module_param(pq_sources, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(pq_sources,
		"Number of p+q source buffers (default: 3)");

अटल पूर्णांक समयout = 3000;
module_param(समयout, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(समयout, "Transfer Timeout in msec (default: 3000), "
		 "Pass -1 for infinite timeout");

अटल bool noverअगरy;
module_param(noverअगरy, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(noverअगरy, "Disable data verification (default: verify)");

अटल bool noअक्रमom;
module_param(noअक्रमom, bool, 0644);
MODULE_PARM_DESC(noअक्रमom, "Disable random offset setup (default: random)");

अटल bool verbose;
module_param(verbose, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(verbose, "Enable \"success\" result messages (default: off)");

अटल पूर्णांक alignment = -1;
module_param(alignment, पूर्णांक, 0644);
MODULE_PARM_DESC(alignment, "Custom data address alignment taken as 2^(alignment) (शेष: not used (-1))");

अटल अचिन्हित पूर्णांक transfer_size;
module_param(transfer_size, uपूर्णांक, 0644);
MODULE_PARM_DESC(transfer_size, "Optional custom transfer size in bytes (default: not used (0))");

अटल bool polled;
module_param(polled, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(polled, "Use polling for completion instead of interrupts");

/**
 * काष्ठा dmatest_params - test parameters.
 * @buf_size:		size of the स_नकल test buffer
 * @channel:		bus ID of the channel to test
 * @device:		bus ID of the DMA Engine to test
 * @thपढ़ोs_per_chan:	number of thपढ़ोs to start per channel
 * @max_channels:	maximum number of channels to use
 * @iterations:		iterations beक्रमe stopping test
 * @xor_sources:	number of xor source buffers
 * @pq_sources:		number of p+q source buffers
 * @समयout:		transfer समयout in msec, -1 क्रम infinite समयout
 * @noverअगरy:		disable data verअगरication
 * @noअक्रमom:		disable अक्रमom offset setup
 * @alignment:		custom data address alignment taken as 2^alignment
 * @transfer_size:	custom transfer size in bytes
 * @polled:		use polling क्रम completion instead of पूर्णांकerrupts
 */
काष्ठा dmatest_params अणु
	अचिन्हित पूर्णांक	buf_size;
	अक्षर		channel[20];
	अक्षर		device[32];
	अचिन्हित पूर्णांक	thपढ़ोs_per_chan;
	अचिन्हित पूर्णांक	max_channels;
	अचिन्हित पूर्णांक	iterations;
	अचिन्हित पूर्णांक	xor_sources;
	अचिन्हित पूर्णांक	pq_sources;
	पूर्णांक		समयout;
	bool		noverअगरy;
	bool		noअक्रमom;
	पूर्णांक		alignment;
	अचिन्हित पूर्णांक	transfer_size;
	bool		polled;
पूर्ण;

/**
 * काष्ठा dmatest_info - test inक्रमmation.
 * @params:		test parameters
 * @channels:		channels under test
 * @nr_channels:	number of channels under test
 * @lock:		access protection to the fields of this काष्ठाure
 * @did_init:		module has been initialized completely
 * @last_error:		test has faced configuration issues
 */
अटल काष्ठा dmatest_info अणु
	/* Test parameters */
	काष्ठा dmatest_params	params;

	/* Internal state */
	काष्ठा list_head	channels;
	अचिन्हित पूर्णांक		nr_channels;
	पूर्णांक			last_error;
	काष्ठा mutex		lock;
	bool			did_init;
पूर्ण test_info = अणु
	.channels = LIST_HEAD_INIT(test_info.channels),
	.lock = __MUTEX_INITIALIZER(test_info.lock),
पूर्ण;

अटल पूर्णांक dmatest_run_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
अटल पूर्णांक dmatest_run_get(अक्षर *val, स्थिर काष्ठा kernel_param *kp);
अटल स्थिर काष्ठा kernel_param_ops run_ops = अणु
	.set = dmatest_run_set,
	.get = dmatest_run_get,
पूर्ण;
अटल bool dmatest_run;
module_param_cb(run, &run_ops, &dmatest_run, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(run, "Run the test (default: false)");

अटल पूर्णांक dmatest_chan_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
अटल पूर्णांक dmatest_chan_get(अक्षर *val, स्थिर काष्ठा kernel_param *kp);
अटल स्थिर काष्ठा kernel_param_ops multi_chan_ops = अणु
	.set = dmatest_chan_set,
	.get = dmatest_chan_get,
पूर्ण;

अटल अक्षर test_channel[20];
अटल काष्ठा kparam_string newchan_kps = अणु
	.string = test_channel,
	.maxlen = 20,
पूर्ण;
module_param_cb(channel, &multi_chan_ops, &newchan_kps, 0644);
MODULE_PARM_DESC(channel, "Bus ID of the channel to test (default: any)");

अटल पूर्णांक dmatest_test_list_get(अक्षर *val, स्थिर काष्ठा kernel_param *kp);
अटल स्थिर काष्ठा kernel_param_ops test_list_ops = अणु
	.get = dmatest_test_list_get,
पूर्ण;
module_param_cb(test_list, &test_list_ops, शून्य, 0444);
MODULE_PARM_DESC(test_list, "Print current test list");

/* Maximum amount of mismatched bytes in buffer to prपूर्णांक */
#घोषणा MAX_ERROR_COUNT		32

/*
 * Initialization patterns. All bytes in the source buffer has bit 7
 * set, all bytes in the destination buffer has bit 7 cleared.
 *
 * Bit 6 is set क्रम all bytes which are to be copied by the DMA
 * engine. Bit 5 is set क्रम all bytes which are to be overwritten by
 * the DMA engine.
 *
 * The reमुख्यing bits are the inverse of a counter which increments by
 * one क्रम each byte address.
 */
#घोषणा PATTERN_SRC		0x80
#घोषणा PATTERN_DST		0x00
#घोषणा PATTERN_COPY		0x40
#घोषणा PATTERN_OVERWRITE	0x20
#घोषणा PATTERN_COUNT_MASK	0x1f
#घोषणा PATTERN_MEMSET_IDX	0x01

/* Fixed poपूर्णांक arithmetic ops */
#घोषणा FIXPT_SHIFT		8
#घोषणा FIXPNT_MASK		0xFF
#घोषणा FIXPT_TO_INT(a)	((a) >> FIXPT_SHIFT)
#घोषणा INT_TO_FIXPT(a)	((a) << FIXPT_SHIFT)
#घोषणा FIXPT_GET_FRAC(a)	((((a) & FIXPNT_MASK) * 100) >> FIXPT_SHIFT)

/* poor man's completion - we want to use रुको_event_मुक्तzable() on it */
काष्ठा dmatest_करोne अणु
	bool			करोne;
	रुको_queue_head_t	*रुको;
पूर्ण;

काष्ठा dmatest_data अणु
	u8		**raw;
	u8		**aligned;
	अचिन्हित पूर्णांक	cnt;
	अचिन्हित पूर्णांक	off;
पूर्ण;

काष्ठा dmatest_thपढ़ो अणु
	काष्ठा list_head	node;
	काष्ठा dmatest_info	*info;
	काष्ठा task_काष्ठा	*task;
	काष्ठा dma_chan		*chan;
	काष्ठा dmatest_data	src;
	काष्ठा dmatest_data	dst;
	क्रमागत dma_transaction_type type;
	रुको_queue_head_t करोne_रुको;
	काष्ठा dmatest_करोne test_करोne;
	bool			करोne;
	bool			pending;
पूर्ण;

काष्ठा dmatest_chan अणु
	काष्ठा list_head	node;
	काष्ठा dma_chan		*chan;
	काष्ठा list_head	thपढ़ोs;
पूर्ण;

अटल DECLARE_WAIT_QUEUE_HEAD(thपढ़ो_रुको);
अटल bool रुको;

अटल bool is_thपढ़ोed_test_run(काष्ठा dmatest_info *info)
अणु
	काष्ठा dmatest_chan *dtc;

	list_क्रम_each_entry(dtc, &info->channels, node) अणु
		काष्ठा dmatest_thपढ़ो *thपढ़ो;

		list_क्रम_each_entry(thपढ़ो, &dtc->thपढ़ोs, node) अणु
			अगर (!thपढ़ो->करोne && !thपढ़ो->pending)
				वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool is_thपढ़ोed_test_pending(काष्ठा dmatest_info *info)
अणु
	काष्ठा dmatest_chan *dtc;

	list_क्रम_each_entry(dtc, &info->channels, node) अणु
		काष्ठा dmatest_thपढ़ो *thपढ़ो;

		list_क्रम_each_entry(thपढ़ो, &dtc->thपढ़ोs, node) अणु
			अगर (thपढ़ो->pending)
				वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक dmatest_रुको_get(अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	काष्ठा dmatest_info *info = &test_info;
	काष्ठा dmatest_params *params = &info->params;

	अगर (params->iterations)
		रुको_event(thपढ़ो_रुको, !is_thपढ़ोed_test_run(info));
	रुको = true;
	वापस param_get_bool(val, kp);
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops रुको_ops = अणु
	.get = dmatest_रुको_get,
	.set = param_set_bool,
पूर्ण;
module_param_cb(रुको, &रुको_ops, &रुको, S_IRUGO);
MODULE_PARM_DESC(रुको, "Wait for tests to complete (default: false)");

अटल bool dmatest_match_channel(काष्ठा dmatest_params *params,
		काष्ठा dma_chan *chan)
अणु
	अगर (params->channel[0] == '\0')
		वापस true;
	वापस म_भेद(dma_chan_name(chan), params->channel) == 0;
पूर्ण

अटल bool dmatest_match_device(काष्ठा dmatest_params *params,
		काष्ठा dma_device *device)
अणु
	अगर (params->device[0] == '\0')
		वापस true;
	वापस म_भेद(dev_name(device->dev), params->device) == 0;
पूर्ण

अटल अचिन्हित दीर्घ dmatest_अक्रमom(व्योम)
अणु
	अचिन्हित दीर्घ buf;

	pअक्रमom_bytes(&buf, माप(buf));
	वापस buf;
पूर्ण

अटल अंतरभूत u8 gen_inv_idx(u8 index, bool is_स_रखो)
अणु
	u8 val = is_स_रखो ? PATTERN_MEMSET_IDX : index;

	वापस ~val & PATTERN_COUNT_MASK;
पूर्ण

अटल अंतरभूत u8 gen_src_value(u8 index, bool is_स_रखो)
अणु
	वापस PATTERN_SRC | gen_inv_idx(index, is_स_रखो);
पूर्ण

अटल अंतरभूत u8 gen_dst_value(u8 index, bool is_स_रखो)
अणु
	वापस PATTERN_DST | gen_inv_idx(index, is_स_रखो);
पूर्ण

अटल व्योम dmatest_init_srcs(u8 **bufs, अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक len,
		अचिन्हित पूर्णांक buf_size, bool is_स_रखो)
अणु
	अचिन्हित पूर्णांक i;
	u8 *buf;

	क्रम (; (buf = *bufs); bufs++) अणु
		क्रम (i = 0; i < start; i++)
			buf[i] = gen_src_value(i, is_स_रखो);
		क्रम ( ; i < start + len; i++)
			buf[i] = gen_src_value(i, is_स_रखो) | PATTERN_COPY;
		क्रम ( ; i < buf_size; i++)
			buf[i] = gen_src_value(i, is_स_रखो);
		buf++;
	पूर्ण
पूर्ण

अटल व्योम dmatest_init_dsts(u8 **bufs, अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक len,
		अचिन्हित पूर्णांक buf_size, bool is_स_रखो)
अणु
	अचिन्हित पूर्णांक i;
	u8 *buf;

	क्रम (; (buf = *bufs); bufs++) अणु
		क्रम (i = 0; i < start; i++)
			buf[i] = gen_dst_value(i, is_स_रखो);
		क्रम ( ; i < start + len; i++)
			buf[i] = gen_dst_value(i, is_स_रखो) |
						PATTERN_OVERWRITE;
		क्रम ( ; i < buf_size; i++)
			buf[i] = gen_dst_value(i, is_स_रखो);
	पूर्ण
पूर्ण

अटल व्योम dmatest_mismatch(u8 actual, u8 pattern, अचिन्हित पूर्णांक index,
		अचिन्हित पूर्णांक counter, bool is_srcbuf, bool is_स_रखो)
अणु
	u8		dअगरf = actual ^ pattern;
	u8		expected = pattern | gen_inv_idx(counter, is_स_रखो);
	स्थिर अक्षर	*thपढ़ो_name = current->comm;

	अगर (is_srcbuf)
		pr_warn("%s: srcbuf[0x%x] overwritten! Expected %02x, got %02x\n",
			thपढ़ो_name, index, expected, actual);
	अन्यथा अगर ((pattern & PATTERN_COPY)
			&& (dअगरf & (PATTERN_COPY | PATTERN_OVERWRITE)))
		pr_warn("%s: dstbuf[0x%x] not copied! Expected %02x, got %02x\n",
			thपढ़ो_name, index, expected, actual);
	अन्यथा अगर (dअगरf & PATTERN_SRC)
		pr_warn("%s: dstbuf[0x%x] was copied! Expected %02x, got %02x\n",
			thपढ़ो_name, index, expected, actual);
	अन्यथा
		pr_warn("%s: dstbuf[0x%x] mismatch! Expected %02x, got %02x\n",
			thपढ़ो_name, index, expected, actual);
पूर्ण

अटल अचिन्हित पूर्णांक dmatest_verअगरy(u8 **bufs, अचिन्हित पूर्णांक start,
		अचिन्हित पूर्णांक end, अचिन्हित पूर्णांक counter, u8 pattern,
		bool is_srcbuf, bool is_स_रखो)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक error_count = 0;
	u8 actual;
	u8 expected;
	u8 *buf;
	अचिन्हित पूर्णांक counter_orig = counter;

	क्रम (; (buf = *bufs); bufs++) अणु
		counter = counter_orig;
		क्रम (i = start; i < end; i++) अणु
			actual = buf[i];
			expected = pattern | gen_inv_idx(counter, is_स_रखो);
			अगर (actual != expected) अणु
				अगर (error_count < MAX_ERROR_COUNT)
					dmatest_mismatch(actual, pattern, i,
							 counter, is_srcbuf,
							 is_स_रखो);
				error_count++;
			पूर्ण
			counter++;
		पूर्ण
	पूर्ण

	अगर (error_count > MAX_ERROR_COUNT)
		pr_warn("%s: %u errors suppressed\n",
			current->comm, error_count - MAX_ERROR_COUNT);

	वापस error_count;
पूर्ण


अटल व्योम dmatest_callback(व्योम *arg)
अणु
	काष्ठा dmatest_करोne *करोne = arg;
	काष्ठा dmatest_thपढ़ो *thपढ़ो =
		container_of(करोne, काष्ठा dmatest_thपढ़ो, test_करोne);
	अगर (!thपढ़ो->करोne) अणु
		करोne->करोne = true;
		wake_up_all(करोne->रुको);
	पूर्ण अन्यथा अणु
		/*
		 * If thपढ़ो->करोne, it means that this callback occurred
		 * after the parent thपढ़ो has cleaned up. This can
		 * happen in the हाल that driver करोesn't implement
		 * the terminate_all() functionality and a dma operation
		 * did not occur within the समयout period
		 */
		WARN(1, "dmatest: Kernel memory may be corrupted!!\n");
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक min_odd(अचिन्हित पूर्णांक x, अचिन्हित पूर्णांक y)
अणु
	अचिन्हित पूर्णांक val = min(x, y);

	वापस val % 2 ? val : val - 1;
पूर्ण

अटल व्योम result(स्थिर अक्षर *err, अचिन्हित पूर्णांक n, अचिन्हित पूर्णांक src_off,
		   अचिन्हित पूर्णांक dst_off, अचिन्हित पूर्णांक len, अचिन्हित दीर्घ data)
अणु
	अगर (IS_ERR_VALUE(data)) अणु
		pr_info("%s: result #%u: '%s' with src_off=0x%x dst_off=0x%x len=0x%x (%ld)\n",
			current->comm, n, err, src_off, dst_off, len, data);
	पूर्ण अन्यथा अणु
		pr_info("%s: result #%u: '%s' with src_off=0x%x dst_off=0x%x len=0x%x (%lu)\n",
			current->comm, n, err, src_off, dst_off, len, data);
	पूर्ण
पूर्ण

अटल व्योम dbg_result(स्थिर अक्षर *err, अचिन्हित पूर्णांक n, अचिन्हित पूर्णांक src_off,
		       अचिन्हित पूर्णांक dst_off, अचिन्हित पूर्णांक len,
		       अचिन्हित दीर्घ data)
अणु
	pr_debug("%s: result #%u: '%s' with src_off=0x%x dst_off=0x%x len=0x%x (%lu)\n",
		 current->comm, n, err, src_off, dst_off, len, data);
पूर्ण

#घोषणा verbose_result(err, n, src_off, dst_off, len, data) (अणु	\
	अगर (verbose)						\
		result(err, n, src_off, dst_off, len, data);	\
	अन्यथा							\
		dbg_result(err, n, src_off, dst_off, len, data);\
पूर्ण)

अटल अचिन्हित दीर्घ दीर्घ dmatest_persec(s64 runसमय, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित दीर्घ दीर्घ per_sec = 1000000;

	अगर (runसमय <= 0)
		वापस 0;

	/* drop precision until runसमय is 32-bits */
	जबतक (runसमय > अच_पूर्णांक_उच्च) अणु
		runसमय >>= 1;
		per_sec <<= 1;
	पूर्ण

	per_sec *= val;
	per_sec = INT_TO_FIXPT(per_sec);
	करो_भाग(per_sec, runसमय);

	वापस per_sec;
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ dmatest_KBs(s64 runसमय, अचिन्हित दीर्घ दीर्घ len)
अणु
	वापस FIXPT_TO_INT(dmatest_persec(runसमय, len >> 10));
पूर्ण

अटल व्योम __dmatest_मुक्त_test_data(काष्ठा dmatest_data *d, अचिन्हित पूर्णांक cnt)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < cnt; i++)
		kमुक्त(d->raw[i]);

	kमुक्त(d->aligned);
	kमुक्त(d->raw);
पूर्ण

अटल व्योम dmatest_मुक्त_test_data(काष्ठा dmatest_data *d)
अणु
	__dmatest_मुक्त_test_data(d, d->cnt);
पूर्ण

अटल पूर्णांक dmatest_alloc_test_data(काष्ठा dmatest_data *d,
		अचिन्हित पूर्णांक buf_size, u8 align)
अणु
	अचिन्हित पूर्णांक i = 0;

	d->raw = kसुस्मृति(d->cnt + 1, माप(u8 *), GFP_KERNEL);
	अगर (!d->raw)
		वापस -ENOMEM;

	d->aligned = kसुस्मृति(d->cnt + 1, माप(u8 *), GFP_KERNEL);
	अगर (!d->aligned)
		जाओ err;

	क्रम (i = 0; i < d->cnt; i++) अणु
		d->raw[i] = kदो_स्मृति(buf_size + align, GFP_KERNEL);
		अगर (!d->raw[i])
			जाओ err;

		/* align to alignment restriction */
		अगर (align)
			d->aligned[i] = PTR_ALIGN(d->raw[i], align);
		अन्यथा
			d->aligned[i] = d->raw[i];
	पूर्ण

	वापस 0;
err:
	__dmatest_मुक्त_test_data(d, i);
	वापस -ENOMEM;
पूर्ण

/*
 * This function repeatedly tests DMA transfers of various lengths and
 * offsets क्रम a given operation type until it is told to निकास by
 * kthपढ़ो_stop(). There may be multiple thपढ़ोs running this function
 * in parallel क्रम a single channel, and there may be multiple channels
 * being tested in parallel.
 *
 * Beक्रमe each test, the source and destination buffer is initialized
 * with a known pattern. This pattern is dअगरferent depending on
 * whether it's in an area which is supposed to be copied or
 * overwritten, and dअगरferent in the source and destination buffers.
 * So अगर the DMA engine करोesn't copy exactly what we tell it to copy,
 * we'll notice.
 */
अटल पूर्णांक dmatest_func(व्योम *data)
अणु
	काष्ठा dmatest_thपढ़ो	*thपढ़ो = data;
	काष्ठा dmatest_करोne	*करोne = &thपढ़ो->test_करोne;
	काष्ठा dmatest_info	*info;
	काष्ठा dmatest_params	*params;
	काष्ठा dma_chan		*chan;
	काष्ठा dma_device	*dev;
	काष्ठा device		*dma_dev;
	अचिन्हित पूर्णांक		error_count;
	अचिन्हित पूर्णांक		failed_tests = 0;
	अचिन्हित पूर्णांक		total_tests = 0;
	dma_cookie_t		cookie;
	क्रमागत dma_status		status;
	क्रमागत dma_ctrl_flags 	flags;
	u8			*pq_coefs = शून्य;
	पूर्णांक			ret;
	अचिन्हित पूर्णांक 		buf_size;
	काष्ठा dmatest_data	*src;
	काष्ठा dmatest_data	*dst;
	पूर्णांक			i;
	kसमय_प्रकार			kसमय, start, dअगरf;
	kसमय_प्रकार			fillसमय = 0;
	kसमय_प्रकार			compareसमय = 0;
	s64			runसमय = 0;
	अचिन्हित दीर्घ दीर्घ	total_len = 0;
	अचिन्हित दीर्घ दीर्घ	iops = 0;
	u8			align = 0;
	bool			is_स_रखो = false;
	dma_addr_t		*srcs;
	dma_addr_t		*dma_pq;

	set_मुक्तzable();

	ret = -ENOMEM;

	smp_rmb();
	thपढ़ो->pending = false;
	info = thपढ़ो->info;
	params = &info->params;
	chan = thपढ़ो->chan;
	dev = chan->device;
	dma_dev = dmaengine_get_dma_device(chan);

	src = &thपढ़ो->src;
	dst = &thपढ़ो->dst;
	अगर (thपढ़ो->type == DMA_MEMCPY) अणु
		align = params->alignment < 0 ? dev->copy_align :
						params->alignment;
		src->cnt = dst->cnt = 1;
	पूर्ण अन्यथा अगर (thपढ़ो->type == DMA_MEMSET) अणु
		align = params->alignment < 0 ? dev->fill_align :
						params->alignment;
		src->cnt = dst->cnt = 1;
		is_स_रखो = true;
	पूर्ण अन्यथा अगर (thपढ़ो->type == DMA_XOR) अणु
		/* क्रमce odd to ensure dst = src */
		src->cnt = min_odd(params->xor_sources | 1, dev->max_xor);
		dst->cnt = 1;
		align = params->alignment < 0 ? dev->xor_align :
						params->alignment;
	पूर्ण अन्यथा अगर (thपढ़ो->type == DMA_PQ) अणु
		/* क्रमce odd to ensure dst = src */
		src->cnt = min_odd(params->pq_sources | 1, dma_maxpq(dev, 0));
		dst->cnt = 2;
		align = params->alignment < 0 ? dev->pq_align :
						params->alignment;

		pq_coefs = kदो_स्मृति(params->pq_sources + 1, GFP_KERNEL);
		अगर (!pq_coefs)
			जाओ err_thपढ़ो_type;

		क्रम (i = 0; i < src->cnt; i++)
			pq_coefs[i] = 1;
	पूर्ण अन्यथा
		जाओ err_thपढ़ो_type;

	/* Check अगर buffer count fits पूर्णांकo map count variable (u8) */
	अगर ((src->cnt + dst->cnt) >= 255) अणु
		pr_err("too many buffers (%d of 255 supported)\n",
		       src->cnt + dst->cnt);
		जाओ err_मुक्त_coefs;
	पूर्ण

	buf_size = params->buf_size;
	अगर (1 << align > buf_size) अणु
		pr_err("%u-byte buffer too small for %d-byte alignment\n",
		       buf_size, 1 << align);
		जाओ err_मुक्त_coefs;
	पूर्ण

	अगर (dmatest_alloc_test_data(src, buf_size, align) < 0)
		जाओ err_मुक्त_coefs;

	अगर (dmatest_alloc_test_data(dst, buf_size, align) < 0)
		जाओ err_src;

	set_user_nice(current, 10);

	srcs = kसुस्मृति(src->cnt, माप(dma_addr_t), GFP_KERNEL);
	अगर (!srcs)
		जाओ err_dst;

	dma_pq = kसुस्मृति(dst->cnt, माप(dma_addr_t), GFP_KERNEL);
	अगर (!dma_pq)
		जाओ err_srcs_array;

	/*
	 * src and dst buffers are मुक्तd by ourselves below
	 */
	अगर (params->polled)
		flags = DMA_CTRL_ACK;
	अन्यथा
		flags = DMA_CTRL_ACK | DMA_PREP_INTERRUPT;

	kसमय = kसमय_get();
	जबतक (!(kthपढ़ो_should_stop() ||
	       (params->iterations && total_tests >= params->iterations))) अणु
		काष्ठा dma_async_tx_descriptor *tx = शून्य;
		काष्ठा dmaengine_unmap_data *um;
		dma_addr_t *dsts;
		अचिन्हित पूर्णांक len;

		total_tests++;

		अगर (params->transfer_size) अणु
			अगर (params->transfer_size >= buf_size) अणु
				pr_err("%u-byte transfer size must be lower than %u-buffer size\n",
				       params->transfer_size, buf_size);
				अवरोध;
			पूर्ण
			len = params->transfer_size;
		पूर्ण अन्यथा अगर (params->noअक्रमom) अणु
			len = buf_size;
		पूर्ण अन्यथा अणु
			len = dmatest_अक्रमom() % buf_size + 1;
		पूर्ण

		/* Do not alter transfer size explicitly defined by user */
		अगर (!params->transfer_size) अणु
			len = (len >> align) << align;
			अगर (!len)
				len = 1 << align;
		पूर्ण
		total_len += len;

		अगर (params->noअक्रमom) अणु
			src->off = 0;
			dst->off = 0;
		पूर्ण अन्यथा अणु
			src->off = dmatest_अक्रमom() % (buf_size - len + 1);
			dst->off = dmatest_अक्रमom() % (buf_size - len + 1);

			src->off = (src->off >> align) << align;
			dst->off = (dst->off >> align) << align;
		पूर्ण

		अगर (!params->noverअगरy) अणु
			start = kसमय_get();
			dmatest_init_srcs(src->aligned, src->off, len,
					  buf_size, is_स_रखो);
			dmatest_init_dsts(dst->aligned, dst->off, len,
					  buf_size, is_स_रखो);

			dअगरf = kसमय_sub(kसमय_get(), start);
			fillसमय = kसमय_add(fillसमय, dअगरf);
		पूर्ण

		um = dmaengine_get_unmap_data(dma_dev, src->cnt + dst->cnt,
					      GFP_KERNEL);
		अगर (!um) अणु
			failed_tests++;
			result("unmap data NULL", total_tests,
			       src->off, dst->off, len, ret);
			जारी;
		पूर्ण

		um->len = buf_size;
		क्रम (i = 0; i < src->cnt; i++) अणु
			व्योम *buf = src->aligned[i];
			काष्ठा page *pg = virt_to_page(buf);
			अचिन्हित दीर्घ pg_off = offset_in_page(buf);

			um->addr[i] = dma_map_page(dma_dev, pg, pg_off,
						   um->len, DMA_TO_DEVICE);
			srcs[i] = um->addr[i] + src->off;
			ret = dma_mapping_error(dma_dev, um->addr[i]);
			अगर (ret) अणु
				result("src mapping error", total_tests,
				       src->off, dst->off, len, ret);
				जाओ error_unmap_जारी;
			पूर्ण
			um->to_cnt++;
		पूर्ण
		/* map with DMA_BIसूचीECTIONAL to क्रमce ग_लिखोback/invalidate */
		dsts = &um->addr[src->cnt];
		क्रम (i = 0; i < dst->cnt; i++) अणु
			व्योम *buf = dst->aligned[i];
			काष्ठा page *pg = virt_to_page(buf);
			अचिन्हित दीर्घ pg_off = offset_in_page(buf);

			dsts[i] = dma_map_page(dma_dev, pg, pg_off, um->len,
					       DMA_BIसूचीECTIONAL);
			ret = dma_mapping_error(dma_dev, dsts[i]);
			अगर (ret) अणु
				result("dst mapping error", total_tests,
				       src->off, dst->off, len, ret);
				जाओ error_unmap_जारी;
			पूर्ण
			um->bidi_cnt++;
		पूर्ण

		अगर (thपढ़ो->type == DMA_MEMCPY)
			tx = dev->device_prep_dma_स_नकल(chan,
							 dsts[0] + dst->off,
							 srcs[0], len, flags);
		अन्यथा अगर (thपढ़ो->type == DMA_MEMSET)
			tx = dev->device_prep_dma_स_रखो(chan,
						dsts[0] + dst->off,
						*(src->aligned[0] + src->off),
						len, flags);
		अन्यथा अगर (thपढ़ो->type == DMA_XOR)
			tx = dev->device_prep_dma_xor(chan,
						      dsts[0] + dst->off,
						      srcs, src->cnt,
						      len, flags);
		अन्यथा अगर (thपढ़ो->type == DMA_PQ) अणु
			क्रम (i = 0; i < dst->cnt; i++)
				dma_pq[i] = dsts[i] + dst->off;
			tx = dev->device_prep_dma_pq(chan, dma_pq, srcs,
						     src->cnt, pq_coefs,
						     len, flags);
		पूर्ण

		अगर (!tx) अणु
			result("prep error", total_tests, src->off,
			       dst->off, len, ret);
			msleep(100);
			जाओ error_unmap_जारी;
		पूर्ण

		करोne->करोne = false;
		अगर (!params->polled) अणु
			tx->callback = dmatest_callback;
			tx->callback_param = करोne;
		पूर्ण
		cookie = tx->tx_submit(tx);

		अगर (dma_submit_error(cookie)) अणु
			result("submit error", total_tests, src->off,
			       dst->off, len, ret);
			msleep(100);
			जाओ error_unmap_जारी;
		पूर्ण

		अगर (params->polled) अणु
			status = dma_sync_रुको(chan, cookie);
			dmaengine_terminate_sync(chan);
			अगर (status == DMA_COMPLETE)
				करोne->करोne = true;
		पूर्ण अन्यथा अणु
			dma_async_issue_pending(chan);

			रुको_event_मुक्तzable_समयout(thपढ़ो->करोne_रुको,
					करोne->करोne,
					msecs_to_jअगरfies(params->समयout));

			status = dma_async_is_tx_complete(chan, cookie, शून्य,
							  शून्य);
		पूर्ण

		अगर (!करोne->करोne) अणु
			result("test timed out", total_tests, src->off, dst->off,
			       len, 0);
			जाओ error_unmap_जारी;
		पूर्ण अन्यथा अगर (status != DMA_COMPLETE &&
			   !(dma_has_cap(DMA_COMPLETION_NO_ORDER,
					 dev->cap_mask) &&
			     status == DMA_OUT_OF_ORDER)) अणु
			result(status == DMA_ERROR ?
			       "completion error status" :
			       "completion busy status", total_tests, src->off,
			       dst->off, len, ret);
			जाओ error_unmap_जारी;
		पूर्ण

		dmaengine_unmap_put(um);

		अगर (params->noverअगरy) अणु
			verbose_result("test passed", total_tests, src->off,
				       dst->off, len, 0);
			जारी;
		पूर्ण

		start = kसमय_get();
		pr_debug("%s: verifying source buffer...\n", current->comm);
		error_count = dmatest_verअगरy(src->aligned, 0, src->off,
				0, PATTERN_SRC, true, is_स_रखो);
		error_count += dmatest_verअगरy(src->aligned, src->off,
				src->off + len, src->off,
				PATTERN_SRC | PATTERN_COPY, true, is_स_रखो);
		error_count += dmatest_verअगरy(src->aligned, src->off + len,
				buf_size, src->off + len,
				PATTERN_SRC, true, is_स_रखो);

		pr_debug("%s: verifying dest buffer...\n", current->comm);
		error_count += dmatest_verअगरy(dst->aligned, 0, dst->off,
				0, PATTERN_DST, false, is_स_रखो);

		error_count += dmatest_verअगरy(dst->aligned, dst->off,
				dst->off + len, src->off,
				PATTERN_SRC | PATTERN_COPY, false, is_स_रखो);

		error_count += dmatest_verअगरy(dst->aligned, dst->off + len,
				buf_size, dst->off + len,
				PATTERN_DST, false, is_स_रखो);

		dअगरf = kसमय_sub(kसमय_get(), start);
		compareसमय = kसमय_add(compareसमय, dअगरf);

		अगर (error_count) अणु
			result("data error", total_tests, src->off, dst->off,
			       len, error_count);
			failed_tests++;
		पूर्ण अन्यथा अणु
			verbose_result("test passed", total_tests, src->off,
				       dst->off, len, 0);
		पूर्ण

		जारी;

error_unmap_जारी:
		dmaengine_unmap_put(um);
		failed_tests++;
	पूर्ण
	kसमय = kसमय_sub(kसमय_get(), kसमय);
	kसमय = kसमय_sub(kसमय, compareसमय);
	kसमय = kसमय_sub(kसमय, fillसमय);
	runसमय = kसमय_प्रकारo_us(kसमय);

	ret = 0;
	kमुक्त(dma_pq);
err_srcs_array:
	kमुक्त(srcs);
err_dst:
	dmatest_मुक्त_test_data(dst);
err_src:
	dmatest_मुक्त_test_data(src);
err_मुक्त_coefs:
	kमुक्त(pq_coefs);
err_thपढ़ो_type:
	iops = dmatest_persec(runसमय, total_tests);
	pr_info("%s: summary %u tests, %u failures %llu.%02llu iops %llu KB/s (%d)\n",
		current->comm, total_tests, failed_tests,
		FIXPT_TO_INT(iops), FIXPT_GET_FRAC(iops),
		dmatest_KBs(runसमय, total_len), ret);

	/* terminate all transfers on specअगरied channels */
	अगर (ret || failed_tests)
		dmaengine_terminate_sync(chan);

	thपढ़ो->करोne = true;
	wake_up(&thपढ़ो_रुको);

	वापस ret;
पूर्ण

अटल व्योम dmatest_cleanup_channel(काष्ठा dmatest_chan *dtc)
अणु
	काष्ठा dmatest_thपढ़ो	*thपढ़ो;
	काष्ठा dmatest_thपढ़ो	*_thपढ़ो;
	पूर्णांक			ret;

	list_क्रम_each_entry_safe(thपढ़ो, _thपढ़ो, &dtc->thपढ़ोs, node) अणु
		ret = kthपढ़ो_stop(thपढ़ो->task);
		pr_debug("thread %s exited with status %d\n",
			 thपढ़ो->task->comm, ret);
		list_del(&thपढ़ो->node);
		put_task_काष्ठा(thपढ़ो->task);
		kमुक्त(thपढ़ो);
	पूर्ण

	/* terminate all transfers on specअगरied channels */
	dmaengine_terminate_sync(dtc->chan);

	kमुक्त(dtc);
पूर्ण

अटल पूर्णांक dmatest_add_thपढ़ोs(काष्ठा dmatest_info *info,
		काष्ठा dmatest_chan *dtc, क्रमागत dma_transaction_type type)
अणु
	काष्ठा dmatest_params *params = &info->params;
	काष्ठा dmatest_thपढ़ो *thपढ़ो;
	काष्ठा dma_chan *chan = dtc->chan;
	अक्षर *op;
	अचिन्हित पूर्णांक i;

	अगर (type == DMA_MEMCPY)
		op = "copy";
	अन्यथा अगर (type == DMA_MEMSET)
		op = "set";
	अन्यथा अगर (type == DMA_XOR)
		op = "xor";
	अन्यथा अगर (type == DMA_PQ)
		op = "pq";
	अन्यथा
		वापस -EINVAL;

	क्रम (i = 0; i < params->thपढ़ोs_per_chan; i++) अणु
		thपढ़ो = kzalloc(माप(काष्ठा dmatest_thपढ़ो), GFP_KERNEL);
		अगर (!thपढ़ो) अणु
			pr_warn("No memory for %s-%s%u\n",
				dma_chan_name(chan), op, i);
			अवरोध;
		पूर्ण
		thपढ़ो->info = info;
		thपढ़ो->chan = dtc->chan;
		thपढ़ो->type = type;
		thपढ़ो->test_करोne.रुको = &thपढ़ो->करोne_रुको;
		init_रुकोqueue_head(&thपढ़ो->करोne_रुको);
		smp_wmb();
		thपढ़ो->task = kthपढ़ो_create(dmatest_func, thपढ़ो, "%s-%s%u",
				dma_chan_name(chan), op, i);
		अगर (IS_ERR(thपढ़ो->task)) अणु
			pr_warn("Failed to create thread %s-%s%u\n",
				dma_chan_name(chan), op, i);
			kमुक्त(thपढ़ो);
			अवरोध;
		पूर्ण

		/* srcbuf and dstbuf are allocated by the thपढ़ो itself */
		get_task_काष्ठा(thपढ़ो->task);
		list_add_tail(&thपढ़ो->node, &dtc->thपढ़ोs);
		thपढ़ो->pending = true;
	पूर्ण

	वापस i;
पूर्ण

अटल पूर्णांक dmatest_add_channel(काष्ठा dmatest_info *info,
		काष्ठा dma_chan *chan)
अणु
	काष्ठा dmatest_chan	*dtc;
	काष्ठा dma_device	*dma_dev = chan->device;
	अचिन्हित पूर्णांक		thपढ़ो_count = 0;
	पूर्णांक cnt;

	dtc = kदो_स्मृति(माप(काष्ठा dmatest_chan), GFP_KERNEL);
	अगर (!dtc) अणु
		pr_warn("No memory for %s\n", dma_chan_name(chan));
		वापस -ENOMEM;
	पूर्ण

	dtc->chan = chan;
	INIT_LIST_HEAD(&dtc->thपढ़ोs);

	अगर (dma_has_cap(DMA_COMPLETION_NO_ORDER, dma_dev->cap_mask) &&
	    info->params.polled) अणु
		info->params.polled = false;
		pr_warn("DMA_COMPLETION_NO_ORDER, polled disabled\n");
	पूर्ण

	अगर (dma_has_cap(DMA_MEMCPY, dma_dev->cap_mask)) अणु
		अगर (dmatest == 0) अणु
			cnt = dmatest_add_thपढ़ोs(info, dtc, DMA_MEMCPY);
			thपढ़ो_count += cnt > 0 ? cnt : 0;
		पूर्ण
	पूर्ण

	अगर (dma_has_cap(DMA_MEMSET, dma_dev->cap_mask)) अणु
		अगर (dmatest == 1) अणु
			cnt = dmatest_add_thपढ़ोs(info, dtc, DMA_MEMSET);
			thपढ़ो_count += cnt > 0 ? cnt : 0;
		पूर्ण
	पूर्ण

	अगर (dma_has_cap(DMA_XOR, dma_dev->cap_mask)) अणु
		cnt = dmatest_add_thपढ़ोs(info, dtc, DMA_XOR);
		thपढ़ो_count += cnt > 0 ? cnt : 0;
	पूर्ण
	अगर (dma_has_cap(DMA_PQ, dma_dev->cap_mask)) अणु
		cnt = dmatest_add_thपढ़ोs(info, dtc, DMA_PQ);
		thपढ़ो_count += cnt > 0 ? cnt : 0;
	पूर्ण

	pr_info("Added %u threads using %s\n",
		thपढ़ो_count, dma_chan_name(chan));

	list_add_tail(&dtc->node, &info->channels);
	info->nr_channels++;

	वापस 0;
पूर्ण

अटल bool filter(काष्ठा dma_chan *chan, व्योम *param)
अणु
	वापस dmatest_match_channel(param, chan) && dmatest_match_device(param, chan->device);
पूर्ण

अटल व्योम request_channels(काष्ठा dmatest_info *info,
			     क्रमागत dma_transaction_type type)
अणु
	dma_cap_mask_t mask;

	dma_cap_zero(mask);
	dma_cap_set(type, mask);
	क्रम (;;) अणु
		काष्ठा dmatest_params *params = &info->params;
		काष्ठा dma_chan *chan;

		chan = dma_request_channel(mask, filter, params);
		अगर (chan) अणु
			अगर (dmatest_add_channel(info, chan)) अणु
				dma_release_channel(chan);
				अवरोध; /* add_channel failed, punt */
			पूर्ण
		पूर्ण अन्यथा
			अवरोध; /* no more channels available */
		अगर (params->max_channels &&
		    info->nr_channels >= params->max_channels)
			अवरोध; /* we have all we need */
	पूर्ण
पूर्ण

अटल व्योम add_thपढ़ोed_test(काष्ठा dmatest_info *info)
अणु
	काष्ठा dmatest_params *params = &info->params;

	/* Copy test parameters */
	params->buf_size = test_buf_size;
	strlcpy(params->channel, strim(test_channel), माप(params->channel));
	strlcpy(params->device, strim(test_device), माप(params->device));
	params->thपढ़ोs_per_chan = thपढ़ोs_per_chan;
	params->max_channels = max_channels;
	params->iterations = iterations;
	params->xor_sources = xor_sources;
	params->pq_sources = pq_sources;
	params->समयout = समयout;
	params->noverअगरy = noverअगरy;
	params->noअक्रमom = noअक्रमom;
	params->alignment = alignment;
	params->transfer_size = transfer_size;
	params->polled = polled;

	request_channels(info, DMA_MEMCPY);
	request_channels(info, DMA_MEMSET);
	request_channels(info, DMA_XOR);
	request_channels(info, DMA_PQ);
पूर्ण

अटल व्योम run_pending_tests(काष्ठा dmatest_info *info)
अणु
	काष्ठा dmatest_chan *dtc;
	अचिन्हित पूर्णांक thपढ़ो_count = 0;

	list_क्रम_each_entry(dtc, &info->channels, node) अणु
		काष्ठा dmatest_thपढ़ो *thपढ़ो;

		thपढ़ो_count = 0;
		list_क्रम_each_entry(thपढ़ो, &dtc->thपढ़ोs, node) अणु
			wake_up_process(thपढ़ो->task);
			thपढ़ो_count++;
		पूर्ण
		pr_info("Started %u threads using %s\n",
			thपढ़ो_count, dma_chan_name(dtc->chan));
	पूर्ण
पूर्ण

अटल व्योम stop_thपढ़ोed_test(काष्ठा dmatest_info *info)
अणु
	काष्ठा dmatest_chan *dtc, *_dtc;
	काष्ठा dma_chan *chan;

	list_क्रम_each_entry_safe(dtc, _dtc, &info->channels, node) अणु
		list_del(&dtc->node);
		chan = dtc->chan;
		dmatest_cleanup_channel(dtc);
		pr_debug("dropped channel %s\n", dma_chan_name(chan));
		dma_release_channel(chan);
	पूर्ण

	info->nr_channels = 0;
पूर्ण

अटल व्योम start_thपढ़ोed_tests(काष्ठा dmatest_info *info)
अणु
	/* we might be called early to set run=, defer running until all
	 * parameters have been evaluated
	 */
	अगर (!info->did_init)
		वापस;

	run_pending_tests(info);
पूर्ण

अटल पूर्णांक dmatest_run_get(अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	काष्ठा dmatest_info *info = &test_info;

	mutex_lock(&info->lock);
	अगर (is_thपढ़ोed_test_run(info)) अणु
		dmatest_run = true;
	पूर्ण अन्यथा अणु
		अगर (!is_thपढ़ोed_test_pending(info))
			stop_thपढ़ोed_test(info);
		dmatest_run = false;
	पूर्ण
	mutex_unlock(&info->lock);

	वापस param_get_bool(val, kp);
पूर्ण

अटल पूर्णांक dmatest_run_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	काष्ठा dmatest_info *info = &test_info;
	पूर्णांक ret;

	mutex_lock(&info->lock);
	ret = param_set_bool(val, kp);
	अगर (ret) अणु
		mutex_unlock(&info->lock);
		वापस ret;
	पूर्ण अन्यथा अगर (dmatest_run) अणु
		अगर (!is_thपढ़ोed_test_pending(info)) अणु
			/*
			 * We have nothing to run. This can be due to:
			 */
			ret = info->last_error;
			अगर (ret) अणु
				/* 1) Misconfiguration */
				pr_err("Channel misconfigured, can't continue\n");
				mutex_unlock(&info->lock);
				वापस ret;
			पूर्ण अन्यथा अणु
				/* 2) We rely on शेषs */
				pr_info("No channels configured, continue with any\n");
				अगर (!is_thपढ़ोed_test_run(info))
					stop_thपढ़ोed_test(info);
				add_thपढ़ोed_test(info);
			पूर्ण
		पूर्ण
		start_thपढ़ोed_tests(info);
	पूर्ण अन्यथा अणु
		stop_thपढ़ोed_test(info);
	पूर्ण

	mutex_unlock(&info->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक dmatest_chan_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	काष्ठा dmatest_info *info = &test_info;
	काष्ठा dmatest_chan *dtc;
	अक्षर chan_reset_val[20];
	पूर्णांक ret;

	mutex_lock(&info->lock);
	ret = param_set_copystring(val, kp);
	अगर (ret) अणु
		mutex_unlock(&info->lock);
		वापस ret;
	पूर्ण
	/*Clear any previously run thपढ़ोs */
	अगर (!is_thपढ़ोed_test_run(info) && !is_thपढ़ोed_test_pending(info))
		stop_thपढ़ोed_test(info);
	/* Reject channels that are alपढ़ोy रेजिस्टरed */
	अगर (is_thपढ़ोed_test_pending(info)) अणु
		list_क्रम_each_entry(dtc, &info->channels, node) अणु
			अगर (म_भेद(dma_chan_name(dtc->chan),
				   strim(test_channel)) == 0) अणु
				dtc = list_last_entry(&info->channels,
						      काष्ठा dmatest_chan,
						      node);
				strlcpy(chan_reset_val,
					dma_chan_name(dtc->chan),
					माप(chan_reset_val));
				ret = -EBUSY;
				जाओ add_chan_err;
			पूर्ण
		पूर्ण
	पूर्ण

	add_thपढ़ोed_test(info);

	/* Check अगर channel was added successfully */
	अगर (!list_empty(&info->channels)) अणु
		/*
		 * अगर new channel was not successfully added, revert the
		 * "test_channel" string to the name of the last successfully
		 * added channel. exception क्रम when users issues empty string
		 * to channel parameter.
		 */
		dtc = list_last_entry(&info->channels, काष्ठा dmatest_chan, node);
		अगर ((म_भेद(dma_chan_name(dtc->chan), strim(test_channel)) != 0)
		    && (म_भेद("", strim(test_channel)) != 0)) अणु
			ret = -EINVAL;
			strlcpy(chan_reset_val, dma_chan_name(dtc->chan),
				माप(chan_reset_val));
			जाओ add_chan_err;
		पूर्ण

	पूर्ण अन्यथा अणु
		/* Clear test_channel अगर no channels were added successfully */
		strlcpy(chan_reset_val, "", माप(chan_reset_val));
		ret = -EBUSY;
		जाओ add_chan_err;
	पूर्ण

	info->last_error = ret;
	mutex_unlock(&info->lock);

	वापस ret;

add_chan_err:
	param_set_copystring(chan_reset_val, kp);
	info->last_error = ret;
	mutex_unlock(&info->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक dmatest_chan_get(अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	काष्ठा dmatest_info *info = &test_info;

	mutex_lock(&info->lock);
	अगर (!is_thपढ़ोed_test_run(info) && !is_thपढ़ोed_test_pending(info)) अणु
		stop_thपढ़ोed_test(info);
		strlcpy(test_channel, "", माप(test_channel));
	पूर्ण
	mutex_unlock(&info->lock);

	वापस param_get_string(val, kp);
पूर्ण

अटल पूर्णांक dmatest_test_list_get(अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	काष्ठा dmatest_info *info = &test_info;
	काष्ठा dmatest_chan *dtc;
	अचिन्हित पूर्णांक thपढ़ो_count = 0;

	list_क्रम_each_entry(dtc, &info->channels, node) अणु
		काष्ठा dmatest_thपढ़ो *thपढ़ो;

		thपढ़ो_count = 0;
		list_क्रम_each_entry(thपढ़ो, &dtc->thपढ़ोs, node) अणु
			thपढ़ो_count++;
		पूर्ण
		pr_info("%u threads using %s\n",
			thपढ़ो_count, dma_chan_name(dtc->chan));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init dmatest_init(व्योम)
अणु
	काष्ठा dmatest_info *info = &test_info;
	काष्ठा dmatest_params *params = &info->params;

	अगर (dmatest_run) अणु
		mutex_lock(&info->lock);
		add_thपढ़ोed_test(info);
		run_pending_tests(info);
		mutex_unlock(&info->lock);
	पूर्ण

	अगर (params->iterations && रुको)
		रुको_event(thपढ़ो_रुको, !is_thपढ़ोed_test_run(info));

	/* module parameters are stable, initसमय tests are started,
	 * let userspace take over 'run' control
	 */
	info->did_init = true;

	वापस 0;
पूर्ण
/* when compiled-in रुको क्रम drivers to load first */
late_initcall(dmatest_init);

अटल व्योम __निकास dmatest_निकास(व्योम)
अणु
	काष्ठा dmatest_info *info = &test_info;

	mutex_lock(&info->lock);
	stop_thपढ़ोed_test(info);
	mutex_unlock(&info->lock);
पूर्ण
module_निकास(dmatest_निकास);

MODULE_AUTHOR("Haavard Skinnemoen (Atmel)");
MODULE_LICENSE("GPL v2");
