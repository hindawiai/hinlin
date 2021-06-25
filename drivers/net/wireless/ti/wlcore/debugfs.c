<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl1271
 *
 * Copyright (C) 2009 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#समावेश "debugfs.h"

#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "wlcore.h"
#समावेश "debug.h"
#समावेश "acx.h"
#समावेश "ps.h"
#समावेश "io.h"
#समावेश "tx.h"
#समावेश "hw_ops.h"

/* ms */
#घोषणा WL1271_DEBUGFS_STATS_LIFETIME 1000

#घोषणा WLCORE_MAX_BLOCK_SIZE ((माप_प्रकार)(4*PAGE_SIZE))

/* debugfs macros idea from mac80211 */
पूर्णांक wl1271_क्रमmat_buffer(अक्षर __user *userbuf, माप_प्रकार count,
			 loff_t *ppos, अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	अक्षर buf[DEBUGFS_FORMAT_BUFFER_SIZE];
	पूर्णांक res;

	बहु_शुरू(args, fmt);
	res = vscnम_लिखो(buf, माप(buf), fmt, args);
	बहु_पूर्ण(args);

	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, res);
पूर्ण
EXPORT_SYMBOL_GPL(wl1271_क्रमmat_buffer);

व्योम wl1271_debugfs_update_stats(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret;

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	अगर (!wl->plt &&
	    समय_after(jअगरfies, wl->stats.fw_stats_update +
		       msecs_to_jअगरfies(WL1271_DEBUGFS_STATS_LIFETIME))) अणु
		wl1271_acx_statistics(wl, wl->stats.fw_stats);
		wl->stats.fw_stats_update = jअगरfies;
	पूर्ण

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);

out:
	mutex_unlock(&wl->mutex);
पूर्ण
EXPORT_SYMBOL_GPL(wl1271_debugfs_update_stats);

DEBUGFS_READONLY_खाता(retry_count, "%u", wl->stats.retry_count);
DEBUGFS_READONLY_खाता(excessive_retries, "%u",
		      wl->stats.excessive_retries);

अटल sमाप_प्रकार tx_queue_len_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	u32 queue_len;
	अक्षर buf[20];
	पूर्णांक res;

	queue_len = wl1271_tx_total_queue_count(wl);

	res = scnम_लिखो(buf, माप(buf), "%u\n", queue_len);
	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, res);
पूर्ण

अटल स्थिर काष्ठा file_operations tx_queue_len_ops = अणु
	.पढ़ो = tx_queue_len_पढ़ो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल व्योम chip_op_handler(काष्ठा wl1271 *wl, अचिन्हित दीर्घ value,
			    व्योम *arg)
अणु
	पूर्णांक ret;
	पूर्णांक (*chip_op) (काष्ठा wl1271 *wl);

	अगर (!arg) अणु
		wl1271_warning("debugfs chip_op_handler with no callback");
		वापस;
	पूर्ण

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);

		वापस;
	पूर्ण

	chip_op = arg;
	chip_op(wl);

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
पूर्ण

#घोषणा WL12XX_CONF_DEBUGFS(param, conf_sub_काष्ठा,			\
			    min_val, max_val, ग_लिखो_handler_locked,	\
			    ग_लिखो_handler_arg)				\
	अटल sमाप_प्रकार param##_पढ़ो(काष्ठा file *file,			\
				      अक्षर __user *user_buf,		\
				      माप_प्रकार count, loff_t *ppos)	\
	अणु								\
	काष्ठा wl1271 *wl = file->निजी_data;				\
	वापस wl1271_क्रमmat_buffer(user_buf, count,			\
				    ppos, "%d\n",			\
				    wl->conf.conf_sub_काष्ठा.param);	\
	पूर्ण								\
									\
	अटल sमाप_प्रकार param##_ग_लिखो(काष्ठा file *file,			\
				     स्थिर अक्षर __user *user_buf,	\
				     माप_प्रकार count, loff_t *ppos)	\
	अणु								\
	काष्ठा wl1271 *wl = file->निजी_data;				\
	अचिन्हित दीर्घ value;						\
	पूर्णांक ret;							\
									\
	ret = kम_से_अदीर्घ_from_user(user_buf, count, 10, &value);		\
	अगर (ret < 0) अणु							\
		wl1271_warning("illegal value for " #param);		\
		वापस -EINVAL;						\
	पूर्ण								\
									\
	अगर (value < min_val || value > max_val) अणु			\
		wl1271_warning(#param " is not in valid range");	\
		वापस -दुस्फल;						\
	पूर्ण								\
									\
	mutex_lock(&wl->mutex);						\
	wl->conf.conf_sub_काष्ठा.param = value;				\
									\
	ग_लिखो_handler_locked(wl, value, ग_लिखो_handler_arg);		\
									\
	mutex_unlock(&wl->mutex);					\
	वापस count;							\
	पूर्ण								\
									\
	अटल स्थिर काष्ठा file_operations param##_ops = अणु		\
		.पढ़ो = param##_पढ़ो,					\
		.ग_लिखो = param##_ग_लिखो,					\
		.खोलो = simple_खोलो,					\
		.llseek = शेष_llseek,				\
	पूर्ण;

WL12XX_CONF_DEBUGFS(irq_pkt_threshold, rx, 0, 65535,
		    chip_op_handler, wl1271_acx_init_rx_पूर्णांकerrupt)
WL12XX_CONF_DEBUGFS(irq_blk_threshold, rx, 0, 65535,
		    chip_op_handler, wl1271_acx_init_rx_पूर्णांकerrupt)
WL12XX_CONF_DEBUGFS(irq_समयout, rx, 0, 100,
		    chip_op_handler, wl1271_acx_init_rx_पूर्णांकerrupt)

अटल sमाप_प्रकार gpio_घातer_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	bool state = test_bit(WL1271_FLAG_GPIO_POWER, &wl->flags);

	पूर्णांक res;
	अक्षर buf[10];

	res = scnम_लिखो(buf, माप(buf), "%d\n", state);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, res);
पूर्ण

अटल sमाप_प्रकार gpio_घातer_ग_लिखो(काष्ठा file *file,
			   स्थिर अक्षर __user *user_buf,
			   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(user_buf, count, 10, &value);
	अगर (ret < 0) अणु
		wl1271_warning("illegal value in gpio_power");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&wl->mutex);

	अगर (value)
		wl1271_घातer_on(wl);
	अन्यथा
		wl1271_घातer_off(wl);

	mutex_unlock(&wl->mutex);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations gpio_घातer_ops = अणु
	.पढ़ो = gpio_घातer_पढ़ो,
	.ग_लिखो = gpio_घातer_ग_लिखो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार start_recovery_ग_लिखो(काष्ठा file *file,
				    स्थिर अक्षर __user *user_buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;

	mutex_lock(&wl->mutex);
	wl12xx_queue_recovery_work(wl);
	mutex_unlock(&wl->mutex);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations start_recovery_ops = अणु
	.ग_लिखो = start_recovery_ग_लिखो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार dynamic_ps_समयout_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;

	वापस wl1271_क्रमmat_buffer(user_buf, count,
				    ppos, "%d\n",
				    wl->conf.conn.dynamic_ps_समयout);
पूर्ण

अटल sमाप_प्रकार dynamic_ps_समयout_ग_लिखो(काष्ठा file *file,
				    स्थिर अक्षर __user *user_buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	काष्ठा wl12xx_vअगर *wlvअगर;
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(user_buf, count, 10, &value);
	अगर (ret < 0) अणु
		wl1271_warning("illegal value in dynamic_ps");
		वापस -EINVAL;
	पूर्ण

	अगर (value < 1 || value > 65535) अणु
		wl1271_warning("dynamic_ps_timeout is not in valid range");
		वापस -दुस्फल;
	पूर्ण

	mutex_lock(&wl->mutex);

	wl->conf.conn.dynamic_ps_समयout = value;

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	/* In हाल we're alपढ़ोy in PSM, trigger it again to set new समयout
	 * immediately without रुकोing क्रम re-association
	 */

	wl12xx_क्रम_each_wlvअगर_sta(wl, wlvअगर) अणु
		अगर (test_bit(WLVIF_FLAG_IN_PS, &wlvअगर->flags))
			wl1271_ps_set_mode(wl, wlvअगर, STATION_AUTO_PS_MODE);
	पूर्ण

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);

out:
	mutex_unlock(&wl->mutex);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations dynamic_ps_समयout_ops = अणु
	.पढ़ो = dynamic_ps_समयout_पढ़ो,
	.ग_लिखो = dynamic_ps_समयout_ग_लिखो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार क्रमced_ps_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;

	वापस wl1271_क्रमmat_buffer(user_buf, count,
				    ppos, "%d\n",
				    wl->conf.conn.क्रमced_ps);
पूर्ण

अटल sमाप_प्रकार क्रमced_ps_ग_लिखो(काष्ठा file *file,
				    स्थिर अक्षर __user *user_buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	काष्ठा wl12xx_vअगर *wlvअगर;
	अचिन्हित दीर्घ value;
	पूर्णांक ret, ps_mode;

	ret = kम_से_अदीर्घ_from_user(user_buf, count, 10, &value);
	अगर (ret < 0) अणु
		wl1271_warning("illegal value in forced_ps");
		वापस -EINVAL;
	पूर्ण

	अगर (value != 1 && value != 0) अणु
		wl1271_warning("forced_ps should be either 0 or 1");
		वापस -दुस्फल;
	पूर्ण

	mutex_lock(&wl->mutex);

	अगर (wl->conf.conn.क्रमced_ps == value)
		जाओ out;

	wl->conf.conn.क्रमced_ps = value;

	अगर (unlikely(wl->state != WLCORE_STATE_ON))
		जाओ out;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	/* In हाल we're alपढ़ोy in PSM, trigger it again to चयन mode
	 * immediately without रुकोing क्रम re-association
	 */

	ps_mode = value ? STATION_POWER_SAVE_MODE : STATION_AUTO_PS_MODE;

	wl12xx_क्रम_each_wlvअगर_sta(wl, wlvअगर) अणु
		अगर (test_bit(WLVIF_FLAG_IN_PS, &wlvअगर->flags))
			wl1271_ps_set_mode(wl, wlvअगर, ps_mode);
	पूर्ण

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);

out:
	mutex_unlock(&wl->mutex);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations क्रमced_ps_ops = अणु
	.पढ़ो = क्रमced_ps_पढ़ो,
	.ग_लिखो = क्रमced_ps_ग_लिखो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार split_scan_समयout_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;

	वापस wl1271_क्रमmat_buffer(user_buf, count,
				    ppos, "%d\n",
				    wl->conf.scan.split_scan_समयout / 1000);
पूर्ण

अटल sमाप_प्रकार split_scan_समयout_ग_लिखो(काष्ठा file *file,
				    स्थिर अक्षर __user *user_buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(user_buf, count, 10, &value);
	अगर (ret < 0) अणु
		wl1271_warning("illegal value in split_scan_timeout");
		वापस -EINVAL;
	पूर्ण

	अगर (value == 0)
		wl1271_info("split scan will be disabled");

	mutex_lock(&wl->mutex);

	wl->conf.scan.split_scan_समयout = value * 1000;

	mutex_unlock(&wl->mutex);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations split_scan_समयout_ops = अणु
	.पढ़ो = split_scan_समयout_पढ़ो,
	.ग_लिखो = split_scan_समयout_ग_लिखो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार driver_state_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	पूर्णांक res = 0;
	sमाप_प्रकार ret;
	अक्षर *buf;
	काष्ठा wl12xx_vअगर *wlvअगर;

#घोषणा DRIVER_STATE_BUF_LEN 1024

	buf = kदो_स्मृति(DRIVER_STATE_BUF_LEN, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	mutex_lock(&wl->mutex);

#घोषणा DRIVER_STATE_PRINT(x, fmt)   \
	(res += scnम_लिखो(buf + res, DRIVER_STATE_BUF_LEN - res,\
			  #x " = " fmt "\n", wl->x))

#घोषणा DRIVER_STATE_PRINT_GENERIC(x, fmt, args...)   \
	(res += scnम_लिखो(buf + res, DRIVER_STATE_BUF_LEN - res,\
			  #x " = " fmt "\n", args))

#घोषणा DRIVER_STATE_PRINT_LONG(x) DRIVER_STATE_PRINT(x, "%ld")
#घोषणा DRIVER_STATE_PRINT_INT(x)  DRIVER_STATE_PRINT(x, "%d")
#घोषणा DRIVER_STATE_PRINT_STR(x)  DRIVER_STATE_PRINT(x, "%s")
#घोषणा DRIVER_STATE_PRINT_LHEX(x) DRIVER_STATE_PRINT(x, "0x%lx")
#घोषणा DRIVER_STATE_PRINT_HEX(x)  DRIVER_STATE_PRINT(x, "0x%x")

	wl12xx_क्रम_each_wlvअगर_sta(wl, wlvअगर) अणु
		अगर (!test_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvअगर->flags))
			जारी;

		DRIVER_STATE_PRINT_GENERIC(channel, "%d (%s)", wlvअगर->channel,
					   wlvअगर->p2p ? "P2P-CL" : "STA");
	पूर्ण

	wl12xx_क्रम_each_wlvअगर_ap(wl, wlvअगर)
		DRIVER_STATE_PRINT_GENERIC(channel, "%d (%s)", wlvअगर->channel,
					   wlvअगर->p2p ? "P2P-GO" : "AP");

	DRIVER_STATE_PRINT_INT(tx_blocks_available);
	DRIVER_STATE_PRINT_INT(tx_allocated_blocks);
	DRIVER_STATE_PRINT_INT(tx_allocated_pkts[0]);
	DRIVER_STATE_PRINT_INT(tx_allocated_pkts[1]);
	DRIVER_STATE_PRINT_INT(tx_allocated_pkts[2]);
	DRIVER_STATE_PRINT_INT(tx_allocated_pkts[3]);
	DRIVER_STATE_PRINT_INT(tx_frames_cnt);
	DRIVER_STATE_PRINT_LHEX(tx_frames_map[0]);
	DRIVER_STATE_PRINT_INT(tx_queue_count[0]);
	DRIVER_STATE_PRINT_INT(tx_queue_count[1]);
	DRIVER_STATE_PRINT_INT(tx_queue_count[2]);
	DRIVER_STATE_PRINT_INT(tx_queue_count[3]);
	DRIVER_STATE_PRINT_INT(tx_packets_count);
	DRIVER_STATE_PRINT_INT(tx_results_count);
	DRIVER_STATE_PRINT_LHEX(flags);
	DRIVER_STATE_PRINT_INT(tx_blocks_मुक्तd);
	DRIVER_STATE_PRINT_INT(rx_counter);
	DRIVER_STATE_PRINT_INT(state);
	DRIVER_STATE_PRINT_INT(band);
	DRIVER_STATE_PRINT_INT(घातer_level);
	DRIVER_STATE_PRINT_INT(sg_enabled);
	DRIVER_STATE_PRINT_INT(enable_11a);
	DRIVER_STATE_PRINT_INT(noise);
	DRIVER_STATE_PRINT_LHEX(ap_fw_ps_map);
	DRIVER_STATE_PRINT_LHEX(ap_ps_map);
	DRIVER_STATE_PRINT_HEX(quirks);
	DRIVER_STATE_PRINT_HEX(irq);
	/* TODO: ref_घड़ी and tcxo_घड़ी were moved to wl12xx priv */
	DRIVER_STATE_PRINT_HEX(hw_pg_ver);
	DRIVER_STATE_PRINT_HEX(irq_flags);
	DRIVER_STATE_PRINT_HEX(chip.id);
	DRIVER_STATE_PRINT_STR(chip.fw_ver_str);
	DRIVER_STATE_PRINT_STR(chip.phy_fw_ver_str);
	DRIVER_STATE_PRINT_INT(recovery_count);

#अघोषित DRIVER_STATE_PRINT_INT
#अघोषित DRIVER_STATE_PRINT_LONG
#अघोषित DRIVER_STATE_PRINT_HEX
#अघोषित DRIVER_STATE_PRINT_LHEX
#अघोषित DRIVER_STATE_PRINT_STR
#अघोषित DRIVER_STATE_PRINT
#अघोषित DRIVER_STATE_BUF_LEN

	mutex_unlock(&wl->mutex);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, res);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations driver_state_ops = अणु
	.पढ़ो = driver_state_पढ़ो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार vअगरs_state_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	काष्ठा wl12xx_vअगर *wlvअगर;
	पूर्णांक ret, res = 0;
	स्थिर पूर्णांक buf_size = 4096;
	अक्षर *buf;
	अक्षर पंचांगp_buf[64];

	buf = kzalloc(buf_size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	mutex_lock(&wl->mutex);

#घोषणा VIF_STATE_PRINT(x, fmt)				\
	(res += scnम_लिखो(buf + res, buf_size - res,	\
			  #x " = " fmt "\n", wlvअगर->x))

#घोषणा VIF_STATE_PRINT_LONG(x)  VIF_STATE_PRINT(x, "%ld")
#घोषणा VIF_STATE_PRINT_INT(x)   VIF_STATE_PRINT(x, "%d")
#घोषणा VIF_STATE_PRINT_STR(x)   VIF_STATE_PRINT(x, "%s")
#घोषणा VIF_STATE_PRINT_LHEX(x)  VIF_STATE_PRINT(x, "0x%lx")
#घोषणा VIF_STATE_PRINT_LLHEX(x) VIF_STATE_PRINT(x, "0x%llx")
#घोषणा VIF_STATE_PRINT_HEX(x)   VIF_STATE_PRINT(x, "0x%x")

#घोषणा VIF_STATE_PRINT_NSTR(x, len)				\
	करो अणु							\
		स_रखो(पंचांगp_buf, 0, माप(पंचांगp_buf));		\
		स_नकल(पंचांगp_buf, wlvअगर->x,			\
		       min_t(u8, len, माप(पंचांगp_buf) - 1));	\
		res += scnम_लिखो(buf + res, buf_size - res,	\
				 #x " = %s\n", पंचांगp_buf);	\
	पूर्ण जबतक (0)

	wl12xx_क्रम_each_wlvअगर(wl, wlvअगर) अणु
		VIF_STATE_PRINT_INT(role_id);
		VIF_STATE_PRINT_INT(bss_type);
		VIF_STATE_PRINT_LHEX(flags);
		VIF_STATE_PRINT_INT(p2p);
		VIF_STATE_PRINT_INT(dev_role_id);
		VIF_STATE_PRINT_INT(dev_hlid);

		अगर (wlvअगर->bss_type == BSS_TYPE_STA_BSS ||
		    wlvअगर->bss_type == BSS_TYPE_IBSS) अणु
			VIF_STATE_PRINT_INT(sta.hlid);
			VIF_STATE_PRINT_INT(sta.basic_rate_idx);
			VIF_STATE_PRINT_INT(sta.ap_rate_idx);
			VIF_STATE_PRINT_INT(sta.p2p_rate_idx);
			VIF_STATE_PRINT_INT(sta.qos);
		पूर्ण अन्यथा अणु
			VIF_STATE_PRINT_INT(ap.global_hlid);
			VIF_STATE_PRINT_INT(ap.bcast_hlid);
			VIF_STATE_PRINT_LHEX(ap.sta_hlid_map[0]);
			VIF_STATE_PRINT_INT(ap.mgmt_rate_idx);
			VIF_STATE_PRINT_INT(ap.bcast_rate_idx);
			VIF_STATE_PRINT_INT(ap.ucast_rate_idx[0]);
			VIF_STATE_PRINT_INT(ap.ucast_rate_idx[1]);
			VIF_STATE_PRINT_INT(ap.ucast_rate_idx[2]);
			VIF_STATE_PRINT_INT(ap.ucast_rate_idx[3]);
		पूर्ण
		VIF_STATE_PRINT_INT(last_tx_hlid);
		VIF_STATE_PRINT_INT(tx_queue_count[0]);
		VIF_STATE_PRINT_INT(tx_queue_count[1]);
		VIF_STATE_PRINT_INT(tx_queue_count[2]);
		VIF_STATE_PRINT_INT(tx_queue_count[3]);
		VIF_STATE_PRINT_LHEX(links_map[0]);
		VIF_STATE_PRINT_NSTR(ssid, wlvअगर->ssid_len);
		VIF_STATE_PRINT_INT(band);
		VIF_STATE_PRINT_INT(channel);
		VIF_STATE_PRINT_HEX(bitrate_masks[0]);
		VIF_STATE_PRINT_HEX(bitrate_masks[1]);
		VIF_STATE_PRINT_HEX(basic_rate_set);
		VIF_STATE_PRINT_HEX(basic_rate);
		VIF_STATE_PRINT_HEX(rate_set);
		VIF_STATE_PRINT_INT(beacon_पूर्णांक);
		VIF_STATE_PRINT_INT(शेष_key);
		VIF_STATE_PRINT_INT(aid);
		VIF_STATE_PRINT_INT(psm_entry_retry);
		VIF_STATE_PRINT_INT(घातer_level);
		VIF_STATE_PRINT_INT(rssi_thold);
		VIF_STATE_PRINT_INT(last_rssi_event);
		VIF_STATE_PRINT_INT(ba_support);
		VIF_STATE_PRINT_INT(ba_allowed);
		VIF_STATE_PRINT_LLHEX(total_मुक्तd_pkts);
	पूर्ण

#अघोषित VIF_STATE_PRINT_INT
#अघोषित VIF_STATE_PRINT_LONG
#अघोषित VIF_STATE_PRINT_HEX
#अघोषित VIF_STATE_PRINT_LHEX
#अघोषित VIF_STATE_PRINT_LLHEX
#अघोषित VIF_STATE_PRINT_STR
#अघोषित VIF_STATE_PRINT_NSTR
#अघोषित VIF_STATE_PRINT

	mutex_unlock(&wl->mutex);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, res);
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations vअगरs_state_ops = अणु
	.पढ़ो = vअगरs_state_पढ़ो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार dtim_पूर्णांकerval_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	u8 value;

	अगर (wl->conf.conn.wake_up_event == CONF_WAKE_UP_EVENT_DTIM ||
	    wl->conf.conn.wake_up_event == CONF_WAKE_UP_EVENT_N_DTIM)
		value = wl->conf.conn.listen_पूर्णांकerval;
	अन्यथा
		value = 0;

	वापस wl1271_क्रमmat_buffer(user_buf, count, ppos, "%d\n", value);
पूर्ण

अटल sमाप_प्रकार dtim_पूर्णांकerval_ग_लिखो(काष्ठा file *file,
				   स्थिर अक्षर __user *user_buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(user_buf, count, 10, &value);
	अगर (ret < 0) अणु
		wl1271_warning("illegal value for dtim_interval");
		वापस -EINVAL;
	पूर्ण

	अगर (value < 1 || value > 10) अणु
		wl1271_warning("dtim value is not in valid range");
		वापस -दुस्फल;
	पूर्ण

	mutex_lock(&wl->mutex);

	wl->conf.conn.listen_पूर्णांकerval = value;
	/* क्रम some reason there are dअगरferent event types क्रम 1 and >1 */
	अगर (value == 1)
		wl->conf.conn.wake_up_event = CONF_WAKE_UP_EVENT_DTIM;
	अन्यथा
		wl->conf.conn.wake_up_event = CONF_WAKE_UP_EVENT_N_DTIM;

	/*
	 * we करोn't reconfigure ACX_WAKE_UP_CONDITIONS now, so it will only
	 * take effect on the next समय we enter psm.
	 */
	mutex_unlock(&wl->mutex);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations dtim_पूर्णांकerval_ops = अणु
	.पढ़ो = dtim_पूर्णांकerval_पढ़ो,
	.ग_लिखो = dtim_पूर्णांकerval_ग_लिखो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;



अटल sमाप_प्रकार suspend_dtim_पूर्णांकerval_पढ़ो(काष्ठा file *file,
					  अक्षर __user *user_buf,
					  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	u8 value;

	अगर (wl->conf.conn.suspend_wake_up_event == CONF_WAKE_UP_EVENT_DTIM ||
	    wl->conf.conn.suspend_wake_up_event == CONF_WAKE_UP_EVENT_N_DTIM)
		value = wl->conf.conn.suspend_listen_पूर्णांकerval;
	अन्यथा
		value = 0;

	वापस wl1271_क्रमmat_buffer(user_buf, count, ppos, "%d\n", value);
पूर्ण

अटल sमाप_प्रकार suspend_dtim_पूर्णांकerval_ग_लिखो(काष्ठा file *file,
					   स्थिर अक्षर __user *user_buf,
					   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(user_buf, count, 10, &value);
	अगर (ret < 0) अणु
		wl1271_warning("illegal value for suspend_dtim_interval");
		वापस -EINVAL;
	पूर्ण

	अगर (value < 1 || value > 10) अणु
		wl1271_warning("suspend_dtim value is not in valid range");
		वापस -दुस्फल;
	पूर्ण

	mutex_lock(&wl->mutex);

	wl->conf.conn.suspend_listen_पूर्णांकerval = value;
	/* क्रम some reason there are dअगरferent event types क्रम 1 and >1 */
	अगर (value == 1)
		wl->conf.conn.suspend_wake_up_event = CONF_WAKE_UP_EVENT_DTIM;
	अन्यथा
		wl->conf.conn.suspend_wake_up_event = CONF_WAKE_UP_EVENT_N_DTIM;

	mutex_unlock(&wl->mutex);
	वापस count;
पूर्ण


अटल स्थिर काष्ठा file_operations suspend_dtim_पूर्णांकerval_ops = अणु
	.पढ़ो = suspend_dtim_पूर्णांकerval_पढ़ो,
	.ग_लिखो = suspend_dtim_पूर्णांकerval_ग_लिखो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार beacon_पूर्णांकerval_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	u8 value;

	अगर (wl->conf.conn.wake_up_event == CONF_WAKE_UP_EVENT_BEACON ||
	    wl->conf.conn.wake_up_event == CONF_WAKE_UP_EVENT_N_BEACONS)
		value = wl->conf.conn.listen_पूर्णांकerval;
	अन्यथा
		value = 0;

	वापस wl1271_क्रमmat_buffer(user_buf, count, ppos, "%d\n", value);
पूर्ण

अटल sमाप_प्रकार beacon_पूर्णांकerval_ग_लिखो(काष्ठा file *file,
				     स्थिर अक्षर __user *user_buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(user_buf, count, 10, &value);
	अगर (ret < 0) अणु
		wl1271_warning("illegal value for beacon_interval");
		वापस -EINVAL;
	पूर्ण

	अगर (value < 1 || value > 255) अणु
		wl1271_warning("beacon interval value is not in valid range");
		वापस -दुस्फल;
	पूर्ण

	mutex_lock(&wl->mutex);

	wl->conf.conn.listen_पूर्णांकerval = value;
	/* क्रम some reason there are dअगरferent event types क्रम 1 and >1 */
	अगर (value == 1)
		wl->conf.conn.wake_up_event = CONF_WAKE_UP_EVENT_BEACON;
	अन्यथा
		wl->conf.conn.wake_up_event = CONF_WAKE_UP_EVENT_N_BEACONS;

	/*
	 * we करोn't reconfigure ACX_WAKE_UP_CONDITIONS now, so it will only
	 * take effect on the next समय we enter psm.
	 */
	mutex_unlock(&wl->mutex);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations beacon_पूर्णांकerval_ops = अणु
	.पढ़ो = beacon_पूर्णांकerval_पढ़ो,
	.ग_लिखो = beacon_पूर्णांकerval_ग_लिखो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार rx_streaming_पूर्णांकerval_ग_लिखो(काष्ठा file *file,
			   स्थिर अक्षर __user *user_buf,
			   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	काष्ठा wl12xx_vअगर *wlvअगर;
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(user_buf, count, 10, &value);
	अगर (ret < 0) अणु
		wl1271_warning("illegal value in rx_streaming_interval!");
		वापस -EINVAL;
	पूर्ण

	/* valid values: 0, 10-100 */
	अगर (value && (value < 10 || value > 100)) अणु
		wl1271_warning("value is not in range!");
		वापस -दुस्फल;
	पूर्ण

	mutex_lock(&wl->mutex);

	wl->conf.rx_streaming.पूर्णांकerval = value;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	wl12xx_क्रम_each_wlvअगर_sta(wl, wlvअगर) अणु
		wl1271_recalc_rx_streaming(wl, wlvअगर);
	पूर्ण

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);
	वापस count;
पूर्ण

अटल sमाप_प्रकार rx_streaming_पूर्णांकerval_पढ़ो(काष्ठा file *file,
			    अक्षर __user *userbuf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	वापस wl1271_क्रमmat_buffer(userbuf, count, ppos,
				    "%d\n", wl->conf.rx_streaming.पूर्णांकerval);
पूर्ण

अटल स्थिर काष्ठा file_operations rx_streaming_पूर्णांकerval_ops = अणु
	.पढ़ो = rx_streaming_पूर्णांकerval_पढ़ो,
	.ग_लिखो = rx_streaming_पूर्णांकerval_ग_लिखो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार rx_streaming_always_ग_लिखो(काष्ठा file *file,
			   स्थिर अक्षर __user *user_buf,
			   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	काष्ठा wl12xx_vअगर *wlvअगर;
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(user_buf, count, 10, &value);
	अगर (ret < 0) अणु
		wl1271_warning("illegal value in rx_streaming_write!");
		वापस -EINVAL;
	पूर्ण

	/* valid values: 0, 10-100 */
	अगर (!(value == 0 || value == 1)) अणु
		wl1271_warning("value is not in valid!");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&wl->mutex);

	wl->conf.rx_streaming.always = value;

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	wl12xx_क्रम_each_wlvअगर_sta(wl, wlvअगर) अणु
		wl1271_recalc_rx_streaming(wl, wlvअगर);
	पूर्ण

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);
	वापस count;
पूर्ण

अटल sमाप_प्रकार rx_streaming_always_पढ़ो(काष्ठा file *file,
			    अक्षर __user *userbuf,
			    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	वापस wl1271_क्रमmat_buffer(userbuf, count, ppos,
				    "%d\n", wl->conf.rx_streaming.always);
पूर्ण

अटल स्थिर काष्ठा file_operations rx_streaming_always_ops = अणु
	.पढ़ो = rx_streaming_always_पढ़ो,
	.ग_लिखो = rx_streaming_always_ग_लिखो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार beacon_filtering_ग_लिखो(काष्ठा file *file,
				      स्थिर अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	काष्ठा wl12xx_vअगर *wlvअगर;
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(user_buf, count, 0, &value);
	अगर (ret < 0) अणु
		wl1271_warning("illegal value for beacon_filtering!");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&wl->mutex);

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	wl12xx_क्रम_each_wlvअगर(wl, wlvअगर) अणु
		ret = wl1271_acx_beacon_filter_opt(wl, wlvअगर, !!value);
	पूर्ण

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations beacon_filtering_ops = अणु
	.ग_लिखो = beacon_filtering_ग_लिखो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार fw_stats_raw_पढ़ो(काष्ठा file *file,
				 अक्षर __user *userbuf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;

	wl1271_debugfs_update_stats(wl);

	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos,
				       wl->stats.fw_stats,
				       wl->stats.fw_stats_len);
पूर्ण

अटल स्थिर काष्ठा file_operations fw_stats_raw_ops = अणु
	.पढ़ो = fw_stats_raw_पढ़ो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार sleep_auth_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;

	वापस wl1271_क्रमmat_buffer(user_buf, count,
				    ppos, "%d\n",
				    wl->sleep_auth);
पूर्ण

अटल sमाप_प्रकार sleep_auth_ग_लिखो(काष्ठा file *file,
				स्थिर अक्षर __user *user_buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(user_buf, count, 0, &value);
	अगर (ret < 0) अणु
		wl1271_warning("illegal value in sleep_auth");
		वापस -EINVAL;
	पूर्ण

	अगर (value > WL1271_PSM_MAX) अणु
		wl1271_warning("sleep_auth must be between 0 and %d",
			       WL1271_PSM_MAX);
		वापस -दुस्फल;
	पूर्ण

	mutex_lock(&wl->mutex);

	wl->conf.conn.sta_sleep_auth = value;

	अगर (unlikely(wl->state != WLCORE_STATE_ON)) अणु
		/* this will show up on "read" in हाल we are off */
		wl->sleep_auth = value;
		जाओ out;
	पूर्ण

	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		जाओ out;
	पूर्ण

	ret = wl1271_acx_sleep_auth(wl, value);
	अगर (ret < 0)
		जाओ out_sleep;

out_sleep:
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations sleep_auth_ops = अणु
	.पढ़ो = sleep_auth_पढ़ो,
	.ग_लिखो = sleep_auth_ग_लिखो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार dev_mem_पढ़ो(काष्ठा file *file,
	     अक्षर __user *user_buf, माप_प्रकार count,
	     loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	काष्ठा wlcore_partition_set part, old_part;
	माप_प्रकार bytes = count;
	पूर्णांक ret;
	अक्षर *buf;

	/* only requests of dword-aligned size and offset are supported */
	अगर (bytes % 4)
		वापस -EINVAL;

	अगर (*ppos % 4)
		वापस -EINVAL;

	/* function should वापस in reasonable समय */
	bytes = min(bytes, WLCORE_MAX_BLOCK_SIZE);

	अगर (bytes == 0)
		वापस -EINVAL;

	स_रखो(&part, 0, माप(part));
	part.mem.start = *ppos;
	part.mem.size = bytes;

	buf = kदो_स्मृति(bytes, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state == WLCORE_STATE_OFF)) अणु
		ret = -EFAULT;
		जाओ skip_पढ़ो;
	पूर्ण

	/*
	 * Don't fail if elp_wakeup returns an error, so the device's memory
	 * could be पढ़ो even अगर the FW crashed
	 */
	pm_runसमय_get_sync(wl->dev);

	/* store current partition and चयन partition */
	स_नकल(&old_part, &wl->curr_part, माप(old_part));
	ret = wlcore_set_partition(wl, &part);
	अगर (ret < 0)
		जाओ part_err;

	ret = wlcore_raw_पढ़ो(wl, 0, buf, bytes, false);
	अगर (ret < 0)
		जाओ पढ़ो_err;

पढ़ो_err:
	/* recover partition */
	ret = wlcore_set_partition(wl, &old_part);
	अगर (ret < 0)
		जाओ part_err;

part_err:
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);

skip_पढ़ो:
	mutex_unlock(&wl->mutex);

	अगर (ret == 0) अणु
		ret = copy_to_user(user_buf, buf, bytes);
		अगर (ret < bytes) अणु
			bytes -= ret;
			*ppos += bytes;
			ret = 0;
		पूर्ण अन्यथा अणु
			ret = -EFAULT;
		पूर्ण
	पूर्ण

	kमुक्त(buf);

	वापस ((ret == 0) ? bytes : ret);
पूर्ण

अटल sमाप_प्रकार dev_mem_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
		माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	काष्ठा wlcore_partition_set part, old_part;
	माप_प्रकार bytes = count;
	पूर्णांक ret;
	अक्षर *buf;

	/* only requests of dword-aligned size and offset are supported */
	अगर (bytes % 4)
		वापस -EINVAL;

	अगर (*ppos % 4)
		वापस -EINVAL;

	/* function should वापस in reasonable समय */
	bytes = min(bytes, WLCORE_MAX_BLOCK_SIZE);

	अगर (bytes == 0)
		वापस -EINVAL;

	स_रखो(&part, 0, माप(part));
	part.mem.start = *ppos;
	part.mem.size = bytes;

	buf = memdup_user(user_buf, bytes);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	mutex_lock(&wl->mutex);

	अगर (unlikely(wl->state == WLCORE_STATE_OFF)) अणु
		ret = -EFAULT;
		जाओ skip_ग_लिखो;
	पूर्ण

	/*
	 * Don't fail if elp_wakeup returns an error, so the device's memory
	 * could be पढ़ो even अगर the FW crashed
	 */
	pm_runसमय_get_sync(wl->dev);

	/* store current partition and चयन partition */
	स_नकल(&old_part, &wl->curr_part, माप(old_part));
	ret = wlcore_set_partition(wl, &part);
	अगर (ret < 0)
		जाओ part_err;

	ret = wlcore_raw_ग_लिखो(wl, 0, buf, bytes, false);
	अगर (ret < 0)
		जाओ ग_लिखो_err;

ग_लिखो_err:
	/* recover partition */
	ret = wlcore_set_partition(wl, &old_part);
	अगर (ret < 0)
		जाओ part_err;

part_err:
	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);

skip_ग_लिखो:
	mutex_unlock(&wl->mutex);

	अगर (ret == 0)
		*ppos += bytes;

	kमुक्त(buf);

	वापस ((ret == 0) ? bytes : ret);
पूर्ण

अटल loff_t dev_mem_seek(काष्ठा file *file, loff_t offset, पूर्णांक orig)
अणु
	/* only requests of dword-aligned size and offset are supported */
	अगर (offset % 4)
		वापस -EINVAL;

	वापस no_seek_end_llseek(file, offset, orig);
पूर्ण

अटल स्थिर काष्ठा file_operations dev_mem_ops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = dev_mem_पढ़ो,
	.ग_लिखो = dev_mem_ग_लिखो,
	.llseek = dev_mem_seek,
पूर्ण;

अटल sमाप_प्रकार fw_logger_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;

	वापस wl1271_क्रमmat_buffer(user_buf, count,
					ppos, "%d\n",
					wl->conf.fwlog.output);
पूर्ण

अटल sमाप_प्रकार fw_logger_ग_लिखो(काष्ठा file *file,
			       स्थिर अक्षर __user *user_buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wl1271 *wl = file->निजी_data;
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ_from_user(user_buf, count, 0, &value);
	अगर (ret < 0) अणु
		wl1271_warning("illegal value in fw_logger");
		वापस -EINVAL;
	पूर्ण

	अगर ((value > 2) || (value == 0)) अणु
		wl1271_warning("fw_logger value must be 1-UART 2-SDIO");
		वापस -दुस्फल;
	पूर्ण

	अगर (wl->conf.fwlog.output == 0) अणु
		wl1271_warning("invalid operation - fw logger disabled by default, please change mode via wlconf");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&wl->mutex);
	ret = pm_runसमय_get_sync(wl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(wl->dev);
		count = ret;
		जाओ out;
	पूर्ण

	wl->conf.fwlog.output = value;

	ret = wl12xx_cmd_config_fwlog(wl);

	pm_runसमय_mark_last_busy(wl->dev);
	pm_runसमय_put_स्वतःsuspend(wl->dev);

out:
	mutex_unlock(&wl->mutex);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fw_logger_ops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = fw_logger_पढ़ो,
	.ग_लिखो = fw_logger_ग_लिखो,
	.llseek = शेष_llseek,
पूर्ण;

अटल व्योम wl1271_debugfs_add_files(काष्ठा wl1271 *wl,
				     काष्ठा dentry *rootdir)
अणु
	काष्ठा dentry *streaming;

	DEBUGFS_ADD(tx_queue_len, rootdir);
	DEBUGFS_ADD(retry_count, rootdir);
	DEBUGFS_ADD(excessive_retries, rootdir);

	DEBUGFS_ADD(gpio_घातer, rootdir);
	DEBUGFS_ADD(start_recovery, rootdir);
	DEBUGFS_ADD(driver_state, rootdir);
	DEBUGFS_ADD(vअगरs_state, rootdir);
	DEBUGFS_ADD(dtim_पूर्णांकerval, rootdir);
	DEBUGFS_ADD(suspend_dtim_पूर्णांकerval, rootdir);
	DEBUGFS_ADD(beacon_पूर्णांकerval, rootdir);
	DEBUGFS_ADD(beacon_filtering, rootdir);
	DEBUGFS_ADD(dynamic_ps_समयout, rootdir);
	DEBUGFS_ADD(क्रमced_ps, rootdir);
	DEBUGFS_ADD(split_scan_समयout, rootdir);
	DEBUGFS_ADD(irq_pkt_threshold, rootdir);
	DEBUGFS_ADD(irq_blk_threshold, rootdir);
	DEBUGFS_ADD(irq_समयout, rootdir);
	DEBUGFS_ADD(fw_stats_raw, rootdir);
	DEBUGFS_ADD(sleep_auth, rootdir);
	DEBUGFS_ADD(fw_logger, rootdir);

	streaming = debugfs_create_dir("rx_streaming", rootdir);

	DEBUGFS_ADD_PREFIX(rx_streaming, पूर्णांकerval, streaming);
	DEBUGFS_ADD_PREFIX(rx_streaming, always, streaming);

	DEBUGFS_ADD_PREFIX(dev, mem, rootdir);
पूर्ण

व्योम wl1271_debugfs_reset(काष्ठा wl1271 *wl)
अणु
	अगर (!wl->stats.fw_stats)
		वापस;

	स_रखो(wl->stats.fw_stats, 0, wl->stats.fw_stats_len);
	wl->stats.retry_count = 0;
	wl->stats.excessive_retries = 0;
पूर्ण

पूर्णांक wl1271_debugfs_init(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret;
	काष्ठा dentry *rootdir;

	rootdir = debugfs_create_dir(KBUILD_MODNAME,
				     wl->hw->wiphy->debugfsdir);

	wl->stats.fw_stats = kzalloc(wl->stats.fw_stats_len, GFP_KERNEL);
	अगर (!wl->stats.fw_stats) अणु
		ret = -ENOMEM;
		जाओ out_हटाओ;
	पूर्ण

	wl->stats.fw_stats_update = jअगरfies;

	wl1271_debugfs_add_files(wl, rootdir);

	ret = wlcore_debugfs_init(wl, rootdir);
	अगर (ret < 0)
		जाओ out_निकास;

	जाओ out;

out_निकास:
	wl1271_debugfs_निकास(wl);

out_हटाओ:
	debugfs_हटाओ_recursive(rootdir);

out:
	वापस ret;
पूर्ण

व्योम wl1271_debugfs_निकास(काष्ठा wl1271 *wl)
अणु
	kमुक्त(wl->stats.fw_stats);
	wl->stats.fw_stats = शून्य;
पूर्ण
