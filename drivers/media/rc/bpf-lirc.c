<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// bpf-lirc.c - handles bpf
//
// Copyright (C) 2018 Sean Young <sean@mess.org>

#समावेश <linux/bpf.h>
#समावेश <linux/filter.h>
#समावेश <linux/bpf_lirc.h>
#समावेश "rc-core-priv.h"

#घोषणा lirc_rcu_dereference(p)						\
	rcu_dereference_रक्षित(p, lockdep_is_held(&ir_raw_handler_lock))

/*
 * BPF पूर्णांकerface क्रम raw IR
 */
स्थिर काष्ठा bpf_prog_ops lirc_mode2_prog_ops = अणु
पूर्ण;

BPF_CALL_1(bpf_rc_repeat, u32*, sample)
अणु
	काष्ठा ir_raw_event_ctrl *ctrl;

	ctrl = container_of(sample, काष्ठा ir_raw_event_ctrl, bpf_sample);

	rc_repeat(ctrl->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto rc_repeat_proto = अणु
	.func	   = bpf_rc_repeat,
	.gpl_only  = true, /* rc_repeat is EXPORT_SYMBOL_GPL */
	.ret_type  = RET_INTEGER,
	.arg1_type = ARG_PTR_TO_CTX,
पूर्ण;

BPF_CALL_4(bpf_rc_keyकरोwn, u32*, sample, u32, protocol, u64, scancode,
	   u32, toggle)
अणु
	काष्ठा ir_raw_event_ctrl *ctrl;

	ctrl = container_of(sample, काष्ठा ir_raw_event_ctrl, bpf_sample);

	rc_keyकरोwn(ctrl->dev, protocol, scancode, toggle != 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto rc_keyकरोwn_proto = अणु
	.func	   = bpf_rc_keyकरोwn,
	.gpl_only  = true, /* rc_keyकरोwn is EXPORT_SYMBOL_GPL */
	.ret_type  = RET_INTEGER,
	.arg1_type = ARG_PTR_TO_CTX,
	.arg2_type = ARG_ANYTHING,
	.arg3_type = ARG_ANYTHING,
	.arg4_type = ARG_ANYTHING,
पूर्ण;

BPF_CALL_3(bpf_rc_poपूर्णांकer_rel, u32*, sample, s32, rel_x, s32, rel_y)
अणु
	काष्ठा ir_raw_event_ctrl *ctrl;

	ctrl = container_of(sample, काष्ठा ir_raw_event_ctrl, bpf_sample);

	input_report_rel(ctrl->dev->input_dev, REL_X, rel_x);
	input_report_rel(ctrl->dev->input_dev, REL_Y, rel_y);
	input_sync(ctrl->dev->input_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bpf_func_proto rc_poपूर्णांकer_rel_proto = अणु
	.func	   = bpf_rc_poपूर्णांकer_rel,
	.gpl_only  = true,
	.ret_type  = RET_INTEGER,
	.arg1_type = ARG_PTR_TO_CTX,
	.arg2_type = ARG_ANYTHING,
	.arg3_type = ARG_ANYTHING,
पूर्ण;

अटल स्थिर काष्ठा bpf_func_proto *
lirc_mode2_func_proto(क्रमागत bpf_func_id func_id, स्थिर काष्ठा bpf_prog *prog)
अणु
	चयन (func_id) अणु
	हाल BPF_FUNC_rc_repeat:
		वापस &rc_repeat_proto;
	हाल BPF_FUNC_rc_keyकरोwn:
		वापस &rc_keyकरोwn_proto;
	हाल BPF_FUNC_rc_poपूर्णांकer_rel:
		वापस &rc_poपूर्णांकer_rel_proto;
	हाल BPF_FUNC_map_lookup_elem:
		वापस &bpf_map_lookup_elem_proto;
	हाल BPF_FUNC_map_update_elem:
		वापस &bpf_map_update_elem_proto;
	हाल BPF_FUNC_map_delete_elem:
		वापस &bpf_map_delete_elem_proto;
	हाल BPF_FUNC_map_push_elem:
		वापस &bpf_map_push_elem_proto;
	हाल BPF_FUNC_map_pop_elem:
		वापस &bpf_map_pop_elem_proto;
	हाल BPF_FUNC_map_peek_elem:
		वापस &bpf_map_peek_elem_proto;
	हाल BPF_FUNC_kसमय_get_ns:
		वापस &bpf_kसमय_get_ns_proto;
	हाल BPF_FUNC_kसमय_get_boot_ns:
		वापस &bpf_kसमय_get_boot_ns_proto;
	हाल BPF_FUNC_tail_call:
		वापस &bpf_tail_call_proto;
	हाल BPF_FUNC_get_pअक्रमom_u32:
		वापस &bpf_get_pअक्रमom_u32_proto;
	हाल BPF_FUNC_trace_prपूर्णांकk:
		अगर (perfmon_capable())
			वापस bpf_get_trace_prपूर्णांकk_proto();
		fallthrough;
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल bool lirc_mode2_is_valid_access(पूर्णांक off, पूर्णांक size,
				       क्रमागत bpf_access_type type,
				       स्थिर काष्ठा bpf_prog *prog,
				       काष्ठा bpf_insn_access_aux *info)
अणु
	/* We have one field of u32 */
	वापस type == BPF_READ && off == 0 && size == माप(u32);
पूर्ण

स्थिर काष्ठा bpf_verअगरier_ops lirc_mode2_verअगरier_ops = अणु
	.get_func_proto  = lirc_mode2_func_proto,
	.is_valid_access = lirc_mode2_is_valid_access
पूर्ण;

#घोषणा BPF_MAX_PROGS 64

अटल पूर्णांक lirc_bpf_attach(काष्ठा rc_dev *rcdev, काष्ठा bpf_prog *prog)
अणु
	काष्ठा bpf_prog_array *old_array;
	काष्ठा bpf_prog_array *new_array;
	काष्ठा ir_raw_event_ctrl *raw;
	पूर्णांक ret;

	अगर (rcdev->driver_type != RC_DRIVER_IR_RAW)
		वापस -EINVAL;

	ret = mutex_lock_पूर्णांकerruptible(&ir_raw_handler_lock);
	अगर (ret)
		वापस ret;

	raw = rcdev->raw;
	अगर (!raw) अणु
		ret = -ENODEV;
		जाओ unlock;
	पूर्ण

	old_array = lirc_rcu_dereference(raw->progs);
	अगर (old_array && bpf_prog_array_length(old_array) >= BPF_MAX_PROGS) अणु
		ret = -E2BIG;
		जाओ unlock;
	पूर्ण

	ret = bpf_prog_array_copy(old_array, शून्य, prog, &new_array);
	अगर (ret < 0)
		जाओ unlock;

	rcu_assign_poपूर्णांकer(raw->progs, new_array);
	bpf_prog_array_मुक्त(old_array);

unlock:
	mutex_unlock(&ir_raw_handler_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक lirc_bpf_detach(काष्ठा rc_dev *rcdev, काष्ठा bpf_prog *prog)
अणु
	काष्ठा bpf_prog_array *old_array;
	काष्ठा bpf_prog_array *new_array;
	काष्ठा ir_raw_event_ctrl *raw;
	पूर्णांक ret;

	अगर (rcdev->driver_type != RC_DRIVER_IR_RAW)
		वापस -EINVAL;

	ret = mutex_lock_पूर्णांकerruptible(&ir_raw_handler_lock);
	अगर (ret)
		वापस ret;

	raw = rcdev->raw;
	अगर (!raw) अणु
		ret = -ENODEV;
		जाओ unlock;
	पूर्ण

	old_array = lirc_rcu_dereference(raw->progs);
	ret = bpf_prog_array_copy(old_array, prog, शून्य, &new_array);
	/*
	 * Do not use bpf_prog_array_delete_safe() as we would end up
	 * with a dummy entry in the array, and the we would मुक्त the
	 * dummy in lirc_bpf_मुक्त()
	 */
	अगर (ret)
		जाओ unlock;

	rcu_assign_poपूर्णांकer(raw->progs, new_array);
	bpf_prog_array_मुक्त(old_array);
	bpf_prog_put(prog);
unlock:
	mutex_unlock(&ir_raw_handler_lock);
	वापस ret;
पूर्ण

व्योम lirc_bpf_run(काष्ठा rc_dev *rcdev, u32 sample)
अणु
	काष्ठा ir_raw_event_ctrl *raw = rcdev->raw;

	raw->bpf_sample = sample;

	अगर (raw->progs)
		BPF_PROG_RUN_ARRAY(raw->progs, &raw->bpf_sample, BPF_PROG_RUN);
पूर्ण

/*
 * This should be called once the rc thपढ़ो has been stopped, so there can be
 * no concurrent bpf execution.
 *
 * Should be called with the ir_raw_handler_lock held.
 */
व्योम lirc_bpf_मुक्त(काष्ठा rc_dev *rcdev)
अणु
	काष्ठा bpf_prog_array_item *item;
	काष्ठा bpf_prog_array *array;

	array = lirc_rcu_dereference(rcdev->raw->progs);
	अगर (!array)
		वापस;

	क्रम (item = array->items; item->prog; item++)
		bpf_prog_put(item->prog);

	bpf_prog_array_मुक्त(array);
पूर्ण

पूर्णांक lirc_prog_attach(स्थिर जोड़ bpf_attr *attr, काष्ठा bpf_prog *prog)
अणु
	काष्ठा rc_dev *rcdev;
	पूर्णांक ret;

	अगर (attr->attach_flags)
		वापस -EINVAL;

	rcdev = rc_dev_get_from_fd(attr->target_fd);
	अगर (IS_ERR(rcdev))
		वापस PTR_ERR(rcdev);

	ret = lirc_bpf_attach(rcdev, prog);

	put_device(&rcdev->dev);

	वापस ret;
पूर्ण

पूर्णांक lirc_prog_detach(स्थिर जोड़ bpf_attr *attr)
अणु
	काष्ठा bpf_prog *prog;
	काष्ठा rc_dev *rcdev;
	पूर्णांक ret;

	अगर (attr->attach_flags)
		वापस -EINVAL;

	prog = bpf_prog_get_type(attr->attach_bpf_fd,
				 BPF_PROG_TYPE_LIRC_MODE2);
	अगर (IS_ERR(prog))
		वापस PTR_ERR(prog);

	rcdev = rc_dev_get_from_fd(attr->target_fd);
	अगर (IS_ERR(rcdev)) अणु
		bpf_prog_put(prog);
		वापस PTR_ERR(rcdev);
	पूर्ण

	ret = lirc_bpf_detach(rcdev, prog);

	bpf_prog_put(prog);
	put_device(&rcdev->dev);

	वापस ret;
पूर्ण

पूर्णांक lirc_prog_query(स्थिर जोड़ bpf_attr *attr, जोड़ bpf_attr __user *uattr)
अणु
	__u32 __user *prog_ids = u64_to_user_ptr(attr->query.prog_ids);
	काष्ठा bpf_prog_array *progs;
	काष्ठा rc_dev *rcdev;
	u32 cnt, flags = 0;
	पूर्णांक ret;

	अगर (attr->query.query_flags)
		वापस -EINVAL;

	rcdev = rc_dev_get_from_fd(attr->query.target_fd);
	अगर (IS_ERR(rcdev))
		वापस PTR_ERR(rcdev);

	अगर (rcdev->driver_type != RC_DRIVER_IR_RAW) अणु
		ret = -EINVAL;
		जाओ put;
	पूर्ण

	ret = mutex_lock_पूर्णांकerruptible(&ir_raw_handler_lock);
	अगर (ret)
		जाओ put;

	progs = lirc_rcu_dereference(rcdev->raw->progs);
	cnt = progs ? bpf_prog_array_length(progs) : 0;

	अगर (copy_to_user(&uattr->query.prog_cnt, &cnt, माप(cnt))) अणु
		ret = -EFAULT;
		जाओ unlock;
	पूर्ण

	अगर (copy_to_user(&uattr->query.attach_flags, &flags, माप(flags))) अणु
		ret = -EFAULT;
		जाओ unlock;
	पूर्ण

	अगर (attr->query.prog_cnt != 0 && prog_ids && cnt)
		ret = bpf_prog_array_copy_to_user(progs, prog_ids, cnt);

unlock:
	mutex_unlock(&ir_raw_handler_lock);
put:
	put_device(&rcdev->dev);

	वापस ret;
पूर्ण
