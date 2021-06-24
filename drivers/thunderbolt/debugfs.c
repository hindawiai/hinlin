<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Debugfs पूर्णांकerface
 *
 * Copyright (C) 2020, Intel Corporation
 * Authors: Gil Fine <gil.fine@पूर्णांकel.com>
 *	    Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/debugfs.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/uaccess.h>

#समावेश "tb.h"

#घोषणा PORT_CAP_PCIE_LEN	1
#घोषणा PORT_CAP_POWER_LEN	2
#घोषणा PORT_CAP_LANE_LEN	3
#घोषणा PORT_CAP_USB3_LEN	5
#घोषणा PORT_CAP_DP_LEN		8
#घोषणा PORT_CAP_TMU_LEN	8
#घोषणा PORT_CAP_BASIC_LEN	9
#घोषणा PORT_CAP_USB4_LEN	20

#घोषणा SWITCH_CAP_TMU_LEN	26
#घोषणा SWITCH_CAP_BASIC_LEN	27

#घोषणा PATH_LEN		2

#घोषणा COUNTER_SET_LEN		3

#घोषणा DEBUGFS_ATTR(__space, __ग_लिखो)					\
अटल पूर्णांक __space ## _खोलो(काष्ठा inode *inode, काष्ठा file *file)	\
अणु									\
	वापस single_खोलो(file, __space ## _show, inode->i_निजी);	\
पूर्ण									\
									\
अटल स्थिर काष्ठा file_operations __space ## _fops = अणु		\
	.owner = THIS_MODULE,						\
	.खोलो = __space ## _खोलो,					\
	.release = single_release,					\
	.पढ़ो  = seq_पढ़ो,						\
	.ग_लिखो = __ग_लिखो,						\
	.llseek = seq_lseek,						\
पूर्ण

#घोषणा DEBUGFS_ATTR_RO(__space)					\
	DEBUGFS_ATTR(__space, शून्य)

#घोषणा DEBUGFS_ATTR_RW(__space)					\
	DEBUGFS_ATTR(__space, __space ## _ग_लिखो)

अटल काष्ठा dentry *tb_debugfs_root;

अटल व्योम *validate_and_copy_from_user(स्थिर व्योम __user *user_buf,
					 माप_प्रकार *count)
अणु
	माप_प्रकार nbytes;
	व्योम *buf;

	अगर (!*count)
		वापस ERR_PTR(-EINVAL);

	अगर (!access_ok(user_buf, *count))
		वापस ERR_PTR(-EFAULT);

	buf = (व्योम *)get_zeroed_page(GFP_KERNEL);
	अगर (!buf)
		वापस ERR_PTR(-ENOMEM);

	nbytes = min_t(माप_प्रकार, *count, PAGE_SIZE);
	अगर (copy_from_user(buf, user_buf, nbytes)) अणु
		मुक्त_page((अचिन्हित दीर्घ)buf);
		वापस ERR_PTR(-EFAULT);
	पूर्ण

	*count = nbytes;
	वापस buf;
पूर्ण

अटल bool parse_line(अक्षर **line, u32 *offs, u32 *val, पूर्णांक लघु_fmt_len,
		       पूर्णांक दीर्घ_fmt_len)
अणु
	अक्षर *token;
	u32 v[5];
	पूर्णांक ret;

	token = strsep(line, "\n");
	अगर (!token)
		वापस false;

	/*
	 * For Adapter/Router configuration space:
	 * Short क्रमmat is: offset value\न
	 *		    v[0]   v[1]
	 * Long क्रमmat as produced from the पढ़ो side:
	 * offset relative_offset cap_id vs_cap_id value\न
	 * v[0]   v[1]            v[2]   v[3]      v[4]
	 *
	 * For Counter configuration space:
	 * Short क्रमmat is: offset\न
	 *		    v[0]
	 * Long क्रमmat as produced from the पढ़ो side:
	 * offset relative_offset counter_id value\न
	 * v[0]   v[1]            v[2]       v[3]
	 */
	ret = माला_पूछो(token, "%i %i %i %i %i", &v[0], &v[1], &v[2], &v[3], &v[4]);
	/* In हाल of Counters, clear counter, "val" content is NA */
	अगर (ret == लघु_fmt_len) अणु
		*offs = v[0];
		*val = v[लघु_fmt_len - 1];
		वापस true;
	पूर्ण अन्यथा अगर (ret == दीर्घ_fmt_len) अणु
		*offs = v[0];
		*val = v[दीर्घ_fmt_len - 1];
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

#अगर IS_ENABLED(CONFIG_USB4_DEBUGFS_WRITE)
अटल sमाप_प्रकार regs_ग_लिखो(काष्ठा tb_चयन *sw, काष्ठा tb_port *port,
			  स्थिर अक्षर __user *user_buf, माप_प्रकार count,
			  loff_t *ppos)
अणु
	काष्ठा tb *tb = sw->tb;
	अक्षर *line, *buf;
	u32 val, offset;
	पूर्णांक ret = 0;

	buf = validate_and_copy_from_user(user_buf, &count);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	pm_runसमय_get_sync(&sw->dev);

	अगर (mutex_lock_पूर्णांकerruptible(&tb->lock)) अणु
		ret = -ERESTARTSYS;
		जाओ out;
	पूर्ण

	/* User did hardware changes behind the driver's back */
	add_taपूर्णांक(TAINT_USER, LOCKDEP_STILL_OK);

	line = buf;
	जबतक (parse_line(&line, &offset, &val, 2, 5)) अणु
		अगर (port)
			ret = tb_port_ग_लिखो(port, &val, TB_CFG_PORT, offset, 1);
		अन्यथा
			ret = tb_sw_ग_लिखो(sw, &val, TB_CFG_SWITCH, offset, 1);
		अगर (ret)
			अवरोध;
	पूर्ण

	mutex_unlock(&tb->lock);

out:
	pm_runसमय_mark_last_busy(&sw->dev);
	pm_runसमय_put_स्वतःsuspend(&sw->dev);
	मुक्त_page((अचिन्हित दीर्घ)buf);

	वापस ret < 0 ? ret : count;
पूर्ण

अटल sमाप_प्रकार port_regs_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file *s = file->निजी_data;
	काष्ठा tb_port *port = s->निजी;

	वापस regs_ग_लिखो(port->sw, port, user_buf, count, ppos);
पूर्ण

अटल sमाप_प्रकार चयन_regs_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file *s = file->निजी_data;
	काष्ठा tb_चयन *sw = s->निजी;

	वापस regs_ग_लिखो(sw, शून्य, user_buf, count, ppos);
पूर्ण
#घोषणा DEBUGFS_MODE		0600
#अन्यथा
#घोषणा port_regs_ग_लिखो		शून्य
#घोषणा चयन_regs_ग_लिखो	शून्य
#घोषणा DEBUGFS_MODE		0400
#पूर्ण_अगर

अटल पूर्णांक port_clear_all_counters(काष्ठा tb_port *port)
अणु
	u32 *buf;
	पूर्णांक ret;

	buf = kसुस्मृति(COUNTER_SET_LEN * port->config.max_counters, माप(u32),
		      GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = tb_port_ग_लिखो(port, buf, TB_CFG_COUNTERS, 0,
			    COUNTER_SET_LEN * port->config.max_counters);
	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार counters_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा seq_file *s = file->निजी_data;
	काष्ठा tb_port *port = s->निजी;
	काष्ठा tb_चयन *sw = port->sw;
	काष्ठा tb *tb = port->sw->tb;
	अक्षर *buf;
	पूर्णांक ret;

	buf = validate_and_copy_from_user(user_buf, &count);
	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	pm_runसमय_get_sync(&sw->dev);

	अगर (mutex_lock_पूर्णांकerruptible(&tb->lock)) अणु
		ret = -ERESTARTSYS;
		जाओ out;
	पूर्ण

	/* If written delimiter only, clear all counters in one shot */
	अगर (buf[0] == '\n') अणु
		ret = port_clear_all_counters(port);
	पूर्ण अन्यथा  अणु
		अक्षर *line = buf;
		u32 val, offset;

		ret = -EINVAL;
		जबतक (parse_line(&line, &offset, &val, 1, 4)) अणु
			ret = tb_port_ग_लिखो(port, &val, TB_CFG_COUNTERS,
					    offset, 1);
			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&tb->lock);

out:
	pm_runसमय_mark_last_busy(&sw->dev);
	pm_runसमय_put_स्वतःsuspend(&sw->dev);
	मुक्त_page((अचिन्हित दीर्घ)buf);

	वापस ret < 0 ? ret : count;
पूर्ण

अटल व्योम cap_show_by_dw(काष्ठा seq_file *s, काष्ठा tb_चयन *sw,
			   काष्ठा tb_port *port, अचिन्हित पूर्णांक cap,
			   अचिन्हित पूर्णांक offset, u8 cap_id, u8 vsec_id,
			   पूर्णांक dwords)
अणु
	पूर्णांक i, ret;
	u32 data;

	क्रम (i = 0; i < dwords; i++) अणु
		अगर (port)
			ret = tb_port_पढ़ो(port, &data, TB_CFG_PORT, cap + offset + i, 1);
		अन्यथा
			ret = tb_sw_पढ़ो(sw, &data, TB_CFG_SWITCH, cap + offset + i, 1);
		अगर (ret) अणु
			seq_म_लिखो(s, "0x%04x <not accessible>\n", cap + offset + i);
			जारी;
		पूर्ण

		seq_म_लिखो(s, "0x%04x %4d 0x%02x 0x%02x 0x%08x\n", cap + offset + i,
			   offset + i, cap_id, vsec_id, data);
	पूर्ण
पूर्ण

अटल व्योम cap_show(काष्ठा seq_file *s, काष्ठा tb_चयन *sw,
		     काष्ठा tb_port *port, अचिन्हित पूर्णांक cap, u8 cap_id,
		     u8 vsec_id, पूर्णांक length)
अणु
	पूर्णांक ret, offset = 0;

	जबतक (length > 0) अणु
		पूर्णांक i, dwords = min(length, TB_MAX_CONFIG_RW_LENGTH);
		u32 data[TB_MAX_CONFIG_RW_LENGTH];

		अगर (port)
			ret = tb_port_पढ़ो(port, data, TB_CFG_PORT, cap + offset,
					   dwords);
		अन्यथा
			ret = tb_sw_पढ़ो(sw, data, TB_CFG_SWITCH, cap + offset, dwords);
		अगर (ret) अणु
			cap_show_by_dw(s, sw, port, cap, offset, cap_id, vsec_id, length);
			वापस;
		पूर्ण

		क्रम (i = 0; i < dwords; i++) अणु
			seq_म_लिखो(s, "0x%04x %4d 0x%02x 0x%02x 0x%08x\n",
				   cap + offset + i, offset + i,
				   cap_id, vsec_id, data[i]);
		पूर्ण

		length -= dwords;
		offset += dwords;
	पूर्ण
पूर्ण

अटल व्योम port_cap_show(काष्ठा tb_port *port, काष्ठा seq_file *s,
			  अचिन्हित पूर्णांक cap)
अणु
	काष्ठा tb_cap_any header;
	u8 vsec_id = 0;
	माप_प्रकार length;
	पूर्णांक ret;

	ret = tb_port_पढ़ो(port, &header, TB_CFG_PORT, cap, 1);
	अगर (ret) अणु
		seq_म_लिखो(s, "0x%04x <capability read failed>\n", cap);
		वापस;
	पूर्ण

	चयन (header.basic.cap) अणु
	हाल TB_PORT_CAP_PHY:
		length = PORT_CAP_LANE_LEN;
		अवरोध;

	हाल TB_PORT_CAP_TIME1:
		length = PORT_CAP_TMU_LEN;
		अवरोध;

	हाल TB_PORT_CAP_POWER:
		length = PORT_CAP_POWER_LEN;
		अवरोध;

	हाल TB_PORT_CAP_ADAP:
		अगर (tb_port_is_pcie_करोwn(port) || tb_port_is_pcie_up(port)) अणु
			length = PORT_CAP_PCIE_LEN;
		पूर्ण अन्यथा अगर (tb_port_is_dpin(port) || tb_port_is_dpout(port)) अणु
			length = PORT_CAP_DP_LEN;
		पूर्ण अन्यथा अगर (tb_port_is_usb3_करोwn(port) ||
			   tb_port_is_usb3_up(port)) अणु
			length = PORT_CAP_USB3_LEN;
		पूर्ण अन्यथा अणु
			seq_म_लिखो(s, "0x%04x <unsupported capability 0x%02x>\n",
				   cap, header.basic.cap);
			वापस;
		पूर्ण
		अवरोध;

	हाल TB_PORT_CAP_VSE:
		अगर (!header.extended_लघु.length) अणु
			ret = tb_port_पढ़ो(port, (u32 *)&header + 1, TB_CFG_PORT,
					   cap + 1, 1);
			अगर (ret) अणु
				seq_म_लिखो(s, "0x%04x <capability read failed>\n",
					   cap + 1);
				वापस;
			पूर्ण
			length = header.extended_दीर्घ.length;
			vsec_id = header.extended_लघु.vsec_id;
		पूर्ण अन्यथा अणु
			length = header.extended_लघु.length;
			vsec_id = header.extended_लघु.vsec_id;
		पूर्ण
		अवरोध;

	हाल TB_PORT_CAP_USB4:
		length = PORT_CAP_USB4_LEN;
		अवरोध;

	शेष:
		seq_म_लिखो(s, "0x%04x <unsupported capability 0x%02x>\n",
			   cap, header.basic.cap);
		वापस;
	पूर्ण

	cap_show(s, शून्य, port, cap, header.basic.cap, vsec_id, length);
पूर्ण

अटल व्योम port_caps_show(काष्ठा tb_port *port, काष्ठा seq_file *s)
अणु
	पूर्णांक cap;

	cap = tb_port_next_cap(port, 0);
	जबतक (cap > 0) अणु
		port_cap_show(port, s, cap);
		cap = tb_port_next_cap(port, cap);
	पूर्ण
पूर्ण

अटल पूर्णांक port_basic_regs_show(काष्ठा tb_port *port, काष्ठा seq_file *s)
अणु
	u32 data[PORT_CAP_BASIC_LEN];
	पूर्णांक ret, i;

	ret = tb_port_पढ़ो(port, data, TB_CFG_PORT, 0, ARRAY_SIZE(data));
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(data); i++)
		seq_म_लिखो(s, "0x%04x %4d 0x00 0x00 0x%08x\n", i, i, data[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक port_regs_show(काष्ठा seq_file *s, व्योम *not_used)
अणु
	काष्ठा tb_port *port = s->निजी;
	काष्ठा tb_चयन *sw = port->sw;
	काष्ठा tb *tb = sw->tb;
	पूर्णांक ret;

	pm_runसमय_get_sync(&sw->dev);

	अगर (mutex_lock_पूर्णांकerruptible(&tb->lock)) अणु
		ret = -ERESTARTSYS;
		जाओ out_rpm_put;
	पूर्ण

	seq_माला_दो(s, "# offset relative_offset cap_id vs_cap_id value\n");

	ret = port_basic_regs_show(port, s);
	अगर (ret)
		जाओ out_unlock;

	port_caps_show(port, s);

out_unlock:
	mutex_unlock(&tb->lock);
out_rpm_put:
	pm_runसमय_mark_last_busy(&sw->dev);
	pm_runसमय_put_स्वतःsuspend(&sw->dev);

	वापस ret;
पूर्ण
DEBUGFS_ATTR_RW(port_regs);

अटल व्योम चयन_cap_show(काष्ठा tb_चयन *sw, काष्ठा seq_file *s,
			    अचिन्हित पूर्णांक cap)
अणु
	काष्ठा tb_cap_any header;
	पूर्णांक ret, length;
	u8 vsec_id = 0;

	ret = tb_sw_पढ़ो(sw, &header, TB_CFG_SWITCH, cap, 1);
	अगर (ret) अणु
		seq_म_लिखो(s, "0x%04x <capability read failed>\n", cap);
		वापस;
	पूर्ण

	अगर (header.basic.cap == TB_SWITCH_CAP_VSE) अणु
		अगर (!header.extended_लघु.length) अणु
			ret = tb_sw_पढ़ो(sw, (u32 *)&header + 1, TB_CFG_SWITCH,
					 cap + 1, 1);
			अगर (ret) अणु
				seq_म_लिखो(s, "0x%04x <capability read failed>\n",
					   cap + 1);
				वापस;
			पूर्ण
			length = header.extended_दीर्घ.length;
		पूर्ण अन्यथा अणु
			length = header.extended_लघु.length;
		पूर्ण
		vsec_id = header.extended_लघु.vsec_id;
	पूर्ण अन्यथा अणु
		अगर (header.basic.cap == TB_SWITCH_CAP_TMU) अणु
			length = SWITCH_CAP_TMU_LEN;
		पूर्ण अन्यथा  अणु
			seq_म_लिखो(s, "0x%04x <unknown capability 0x%02x>\n",
				   cap, header.basic.cap);
			वापस;
		पूर्ण
	पूर्ण

	cap_show(s, sw, शून्य, cap, header.basic.cap, vsec_id, length);
पूर्ण

अटल व्योम चयन_caps_show(काष्ठा tb_चयन *sw, काष्ठा seq_file *s)
अणु
	पूर्णांक cap;

	cap = tb_चयन_next_cap(sw, 0);
	जबतक (cap > 0) अणु
		चयन_cap_show(sw, s, cap);
		cap = tb_चयन_next_cap(sw, cap);
	पूर्ण
पूर्ण

अटल पूर्णांक चयन_basic_regs_show(काष्ठा tb_चयन *sw, काष्ठा seq_file *s)
अणु
	u32 data[SWITCH_CAP_BASIC_LEN];
	माप_प्रकार dwords;
	पूर्णांक ret, i;

	/* Only USB4 has the additional रेजिस्टरs */
	अगर (tb_चयन_is_usb4(sw))
		dwords = ARRAY_SIZE(data);
	अन्यथा
		dwords = 7;

	ret = tb_sw_पढ़ो(sw, data, TB_CFG_SWITCH, 0, dwords);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < dwords; i++)
		seq_म_लिखो(s, "0x%04x %4d 0x00 0x00 0x%08x\n", i, i, data[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक चयन_regs_show(काष्ठा seq_file *s, व्योम *not_used)
अणु
	काष्ठा tb_चयन *sw = s->निजी;
	काष्ठा tb *tb = sw->tb;
	पूर्णांक ret;

	pm_runसमय_get_sync(&sw->dev);

	अगर (mutex_lock_पूर्णांकerruptible(&tb->lock)) अणु
		ret = -ERESTARTSYS;
		जाओ out_rpm_put;
	पूर्ण

	seq_माला_दो(s, "# offset relative_offset cap_id vs_cap_id value\n");

	ret = चयन_basic_regs_show(sw, s);
	अगर (ret)
		जाओ out_unlock;

	चयन_caps_show(sw, s);

out_unlock:
	mutex_unlock(&tb->lock);
out_rpm_put:
	pm_runसमय_mark_last_busy(&sw->dev);
	pm_runसमय_put_स्वतःsuspend(&sw->dev);

	वापस ret;
पूर्ण
DEBUGFS_ATTR_RW(चयन_regs);

अटल पूर्णांक path_show_one(काष्ठा tb_port *port, काष्ठा seq_file *s, पूर्णांक hopid)
अणु
	u32 data[PATH_LEN];
	पूर्णांक ret, i;

	ret = tb_port_पढ़ो(port, data, TB_CFG_HOPS, hopid * PATH_LEN,
			   ARRAY_SIZE(data));
	अगर (ret) अणु
		seq_म_लिखो(s, "0x%04x <not accessible>\n", hopid * PATH_LEN);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(data); i++) अणु
		seq_म_लिखो(s, "0x%04x %4d 0x%02x 0x%08x\n",
			   hopid * PATH_LEN + i, i, hopid, data[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक path_show(काष्ठा seq_file *s, व्योम *not_used)
अणु
	काष्ठा tb_port *port = s->निजी;
	काष्ठा tb_चयन *sw = port->sw;
	काष्ठा tb *tb = sw->tb;
	पूर्णांक start, i, ret = 0;

	pm_runसमय_get_sync(&sw->dev);

	अगर (mutex_lock_पूर्णांकerruptible(&tb->lock)) अणु
		ret = -ERESTARTSYS;
		जाओ out_rpm_put;
	पूर्ण

	seq_माला_दो(s, "# offset relative_offset in_hop_id value\n");

	/* NHI and lane adapters have entry क्रम path 0 */
	अगर (tb_port_is_null(port) || tb_port_is_nhi(port)) अणु
		ret = path_show_one(port, s, 0);
		अगर (ret)
			जाओ out_unlock;
	पूर्ण

	start = tb_port_is_nhi(port) ? 1 : TB_PATH_MIN_HOPID;

	क्रम (i = start; i <= port->config.max_in_hop_id; i++) अणु
		ret = path_show_one(port, s, i);
		अगर (ret)
			अवरोध;
	पूर्ण

out_unlock:
	mutex_unlock(&tb->lock);
out_rpm_put:
	pm_runसमय_mark_last_busy(&sw->dev);
	pm_runसमय_put_स्वतःsuspend(&sw->dev);

	वापस ret;
पूर्ण
DEBUGFS_ATTR_RO(path);

अटल पूर्णांक counter_set_regs_show(काष्ठा tb_port *port, काष्ठा seq_file *s,
				 पूर्णांक counter)
अणु
	u32 data[COUNTER_SET_LEN];
	पूर्णांक ret, i;

	ret = tb_port_पढ़ो(port, data, TB_CFG_COUNTERS,
			   counter * COUNTER_SET_LEN, ARRAY_SIZE(data));
	अगर (ret) अणु
		seq_म_लिखो(s, "0x%04x <not accessible>\n",
			   counter * COUNTER_SET_LEN);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(data); i++) अणु
		seq_म_लिखो(s, "0x%04x %4d 0x%02x 0x%08x\n",
			   counter * COUNTER_SET_LEN + i, i, counter, data[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक counters_show(काष्ठा seq_file *s, व्योम *not_used)
अणु
	काष्ठा tb_port *port = s->निजी;
	काष्ठा tb_चयन *sw = port->sw;
	काष्ठा tb *tb = sw->tb;
	पूर्णांक i, ret = 0;

	pm_runसमय_get_sync(&sw->dev);

	अगर (mutex_lock_पूर्णांकerruptible(&tb->lock)) अणु
		ret = -ERESTARTSYS;
		जाओ out;
	पूर्ण

	seq_माला_दो(s, "# offset relative_offset counter_id value\n");

	क्रम (i = 0; i < port->config.max_counters; i++) अणु
		ret = counter_set_regs_show(port, s, i);
		अगर (ret)
			अवरोध;
	पूर्ण

	mutex_unlock(&tb->lock);

out:
	pm_runसमय_mark_last_busy(&sw->dev);
	pm_runसमय_put_स्वतःsuspend(&sw->dev);

	वापस ret;
पूर्ण
DEBUGFS_ATTR_RW(counters);

/**
 * tb_चयन_debugfs_init() - Add debugfs entries क्रम router
 * @sw: Poपूर्णांकer to the router
 *
 * Adds debugfs directories and files क्रम given router.
 */
व्योम tb_चयन_debugfs_init(काष्ठा tb_चयन *sw)
अणु
	काष्ठा dentry *debugfs_dir;
	काष्ठा tb_port *port;

	debugfs_dir = debugfs_create_dir(dev_name(&sw->dev), tb_debugfs_root);
	sw->debugfs_dir = debugfs_dir;
	debugfs_create_file("regs", DEBUGFS_MODE, debugfs_dir, sw,
			    &चयन_regs_fops);

	tb_चयन_क्रम_each_port(sw, port) अणु
		काष्ठा dentry *debugfs_dir;
		अक्षर dir_name[10];

		अगर (port->disabled)
			जारी;
		अगर (port->config.type == TB_TYPE_INACTIVE)
			जारी;

		snम_लिखो(dir_name, माप(dir_name), "port%d", port->port);
		debugfs_dir = debugfs_create_dir(dir_name, sw->debugfs_dir);
		debugfs_create_file("regs", DEBUGFS_MODE, debugfs_dir,
				    port, &port_regs_fops);
		debugfs_create_file("path", 0400, debugfs_dir, port,
				    &path_fops);
		अगर (port->config.counters_support)
			debugfs_create_file("counters", 0600, debugfs_dir, port,
					    &counters_fops);
	पूर्ण
पूर्ण

/**
 * tb_चयन_debugfs_हटाओ() - Remove all router debugfs entries
 * @sw: Poपूर्णांकer to the router
 *
 * Removes all previously added debugfs entries under this router.
 */
व्योम tb_चयन_debugfs_हटाओ(काष्ठा tb_चयन *sw)
अणु
	debugfs_हटाओ_recursive(sw->debugfs_dir);
पूर्ण

/**
 * tb_service_debugfs_init() - Add debugfs directory क्रम service
 * @svc: Thunderbolt service poपूर्णांकer
 *
 * Adds debugfs directory क्रम service.
 */
व्योम tb_service_debugfs_init(काष्ठा tb_service *svc)
अणु
	svc->debugfs_dir = debugfs_create_dir(dev_name(&svc->dev),
					      tb_debugfs_root);
पूर्ण

/**
 * tb_service_debugfs_हटाओ() - Remove service debugfs directory
 * @svc: Thunderbolt service poपूर्णांकer
 *
 * Removes the previously created debugfs directory क्रम @svc.
 */
व्योम tb_service_debugfs_हटाओ(काष्ठा tb_service *svc)
अणु
	debugfs_हटाओ_recursive(svc->debugfs_dir);
	svc->debugfs_dir = शून्य;
पूर्ण

व्योम tb_debugfs_init(व्योम)
अणु
	tb_debugfs_root = debugfs_create_dir("thunderbolt", शून्य);
पूर्ण

व्योम tb_debugfs_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(tb_debugfs_root);
पूर्ण
