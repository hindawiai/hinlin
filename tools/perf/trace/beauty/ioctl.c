<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1
/*
 * trace/beauty/ioctl.c
 *
 *  Copyright (C) 2017, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
 */

#समावेश "trace/beauty/beauty.h"
#समावेश <linux/kernel.h>

/*
 * FIXME: to support all arches we have to improve this, क्रम
 * now, to build on older प्रणालीs without things like TIOCGEXCL,
 * get it directly from our copy.
 *
 * Right now only x86 is being supported क्रम beautअगरying ioctl args
 * in 'perf trace', see tools/perf/trace/beauty/Build and builtin-trace.c
 */
#समावेश <uapi/यंत्र-generic/ioctls.h>

अटल माप_प्रकार ioctl__scnम_लिखो_tty_cmd(पूर्णांक nr, पूर्णांक dir, अक्षर *bf, माप_प्रकार size)
अणु
	अटल स्थिर अक्षर *ioctl_tty_cmd[] = अणु
	[_IOC_NR(TCGETS)] = "TCGETS", "TCSETS", "TCSETSW", "TCSETSF", "TCGETA", "TCSETA", "TCSETAW",
	"TCSETAF", "TCSBRK", "TCXONC", "TCFLSH", "TIOCEXCL", "TIOCNXCL", "TIOCSCTTY",
	"TIOCGPGRP", "TIOCSPGRP", "TIOCOUTQ", "TIOCSTI", "TIOCGWINSZ", "TIOCSWINSZ",
	"TIOCMGET", "TIOCMBIS", "TIOCMBIC", "TIOCMSET", "TIOCGSOFTCAR", "TIOCSSOFTCAR",
	"FIONREAD", "TIOCLINUX", "TIOCCONS", "TIOCGSERIAL", "TIOCSSERIAL", "TIOCPKT",
	"FIONBIO", "TIOCNOTTY", "TIOCSETD", "TIOCGETD", "TCSBRKP",
	[_IOC_NR(TIOCSBRK)] = "TIOCSBRK", "TIOCCBRK", "TIOCGSID", "TCGETS2", "TCSETS2",
	"TCSETSW2", "TCSETSF2", "TIOCGRS48", "TIOCSRS485", "TIOCGPTN", "TIOCSPTLCK",
	"TIOCGDEV", "TCSETX", "TCSETXF", "TCSETXW", "TIOCSIG", "TIOCVHANGUP", "TIOCGPKT",
	"TIOCGPTLCK", [_IOC_NR(TIOCGEXCL)] = "TIOCGEXCL", "TIOCGPTPEER",
	"TIOCGISO7816", "TIOCSISO7816",
	[_IOC_NR(FIONCLEX)] = "FIONCLEX", "FIOCLEX", "FIOASYNC", "TIOCSERCONFIG",
	"TIOCSERGWILD", "TIOCSERSWILD", "TIOCGLCKTRMIOS", "TIOCSLCKTRMIOS",
	"TIOCSERGSTRUCT", "TIOCSERGETLSR", "TIOCSERGETMULTI", "TIOCSERSETMULTI",
	"TIOCMIWAIT", "TIOCGICOUNT", पूर्ण;
	अटल DEFINE_STRARRAY(ioctl_tty_cmd, "");

	अगर (nr < strarray__ioctl_tty_cmd.nr_entries && strarray__ioctl_tty_cmd.entries[nr] != शून्य)
		वापस scnम_लिखो(bf, size, "%s", strarray__ioctl_tty_cmd.entries[nr]);

	वापस scnम_लिखो(bf, size, "(%#x, %#x, %#x)", 'T', nr, dir);
पूर्ण

अटल माप_प्रकार ioctl__scnम_लिखो_drm_cmd(पूर्णांक nr, पूर्णांक dir, अक्षर *bf, माप_प्रकार size)
अणु
#समावेश "trace/beauty/generated/ioctl/drm_ioctl_array.c"
	अटल DEFINE_STRARRAY(drm_ioctl_cmds, "");

	अगर (nr < strarray__drm_ioctl_cmds.nr_entries && strarray__drm_ioctl_cmds.entries[nr] != शून्य)
		वापस scnम_लिखो(bf, size, "DRM_%s", strarray__drm_ioctl_cmds.entries[nr]);

	वापस scnम_लिखो(bf, size, "(%#x, %#x, %#x)", 'd', nr, dir);
पूर्ण

अटल माप_प्रकार ioctl__scnम_लिखो_sndrv_pcm_cmd(पूर्णांक nr, पूर्णांक dir, अक्षर *bf, माप_प्रकार size)
अणु
#समावेश "trace/beauty/generated/ioctl/sndrv_pcm_ioctl_array.c"
	अटल DEFINE_STRARRAY(sndrv_pcm_ioctl_cmds, "");

	अगर (nr < strarray__sndrv_pcm_ioctl_cmds.nr_entries && strarray__sndrv_pcm_ioctl_cmds.entries[nr] != शून्य)
		वापस scnम_लिखो(bf, size, "SNDRV_PCM_%s", strarray__sndrv_pcm_ioctl_cmds.entries[nr]);

	वापस scnम_लिखो(bf, size, "(%#x, %#x, %#x)", 'A', nr, dir);
पूर्ण

अटल माप_प्रकार ioctl__scnम_लिखो_sndrv_ctl_cmd(पूर्णांक nr, पूर्णांक dir, अक्षर *bf, माप_प्रकार size)
अणु
#समावेश "trace/beauty/generated/ioctl/sndrv_ctl_ioctl_array.c"
	अटल DEFINE_STRARRAY(sndrv_ctl_ioctl_cmds, "");

	अगर (nr < strarray__sndrv_ctl_ioctl_cmds.nr_entries && strarray__sndrv_ctl_ioctl_cmds.entries[nr] != शून्य)
		वापस scnम_लिखो(bf, size, "SNDRV_CTL_%s", strarray__sndrv_ctl_ioctl_cmds.entries[nr]);

	वापस scnम_लिखो(bf, size, "(%#x, %#x, %#x)", 'U', nr, dir);
पूर्ण

अटल माप_प्रकार ioctl__scnम_लिखो_kvm_cmd(पूर्णांक nr, पूर्णांक dir, अक्षर *bf, माप_प्रकार size)
अणु
#समावेश "trace/beauty/generated/ioctl/kvm_ioctl_array.c"
	अटल DEFINE_STRARRAY(kvm_ioctl_cmds, "");

	अगर (nr < strarray__kvm_ioctl_cmds.nr_entries && strarray__kvm_ioctl_cmds.entries[nr] != शून्य)
		वापस scnम_लिखो(bf, size, "KVM_%s", strarray__kvm_ioctl_cmds.entries[nr]);

	वापस scnम_लिखो(bf, size, "(%#x, %#x, %#x)", 0xAE, nr, dir);
पूर्ण

अटल माप_प्रकार ioctl__scnम_लिखो_vhost_virtio_cmd(पूर्णांक nr, पूर्णांक dir, अक्षर *bf, माप_प्रकार size)
अणु
#समावेश "trace/beauty/generated/ioctl/vhost_virtio_ioctl_array.c"
	अटल DEFINE_STRARRAY(vhost_virtio_ioctl_cmds, "");
	अटल DEFINE_STRARRAY(vhost_virtio_ioctl_पढ़ो_cmds, "");
	काष्ठा strarray *s = (dir & _IOC_READ) ? &strarray__vhost_virtio_ioctl_पढ़ो_cmds : &strarray__vhost_virtio_ioctl_cmds;

	अगर (nr < s->nr_entries && s->entries[nr] != शून्य)
		वापस scnम_लिखो(bf, size, "VHOST_%s", s->entries[nr]);

	वापस scnम_लिखो(bf, size, "(%#x, %#x, %#x)", 0xAF, nr, dir);
पूर्ण

अटल माप_प्रकार ioctl__scnम_लिखो_perf_cmd(पूर्णांक nr, पूर्णांक dir, अक्षर *bf, माप_प्रकार size)
अणु
#समावेश "trace/beauty/generated/ioctl/perf_ioctl_array.c"
	अटल DEFINE_STRARRAY(perf_ioctl_cmds, "");

	अगर (nr < strarray__perf_ioctl_cmds.nr_entries && strarray__perf_ioctl_cmds.entries[nr] != शून्य)
		वापस scnम_लिखो(bf, size, "PERF_%s", strarray__perf_ioctl_cmds.entries[nr]);

	वापस scnम_लिखो(bf, size, "(%#x, %#x, %#x)", 0xAE, nr, dir);
पूर्ण

अटल माप_प्रकार ioctl__scnम_लिखो_usbdevfs_cmd(पूर्णांक nr, पूर्णांक dir, अक्षर *bf, माप_प्रकार size)
अणु
#समावेश "trace/beauty/generated/ioctl/usbdevfs_ioctl_array.c"
	अटल DEFINE_STRARRAY(usbdevfs_ioctl_cmds, "");

	अगर (nr < strarray__usbdevfs_ioctl_cmds.nr_entries && strarray__usbdevfs_ioctl_cmds.entries[nr] != शून्य)
		वापस scnम_लिखो(bf, size, "USBDEVFS_%s", strarray__usbdevfs_ioctl_cmds.entries[nr]);

	वापस scnम_लिखो(bf, size, "(%c, %#x, %#x)", 'U', nr, dir);
पूर्ण

अटल माप_प्रकार ioctl__scnम_लिखो_cmd(अचिन्हित दीर्घ cmd, अक्षर *bf, माप_प्रकार size, bool show_prefix)
अणु
	स्थिर अक्षर *prefix = "_IOC_";
	पूर्णांक dir	 = _IOC_सूची(cmd),
	    type = _IOC_TYPE(cmd),
	    nr	 = _IOC_NR(cmd),
	    sz	 = _IOC_SIZE(cmd);
	पूर्णांक prपूर्णांकed = 0;
	अटल स्थिर काष्ठा ioctl_type अणु
		पूर्णांक	type;
		माप_प्रकार	(*scnम_लिखो)(पूर्णांक nr, पूर्णांक dir, अक्षर *bf, माप_प्रकार size);
	पूर्ण ioctl_types[] = अणु /* Must be ordered by type */
			      अणु .type	= '$', .scnम_लिखो = ioctl__scnम_लिखो_perf_cmd, पूर्ण,
		['A' - '$'] = { .type	= 'A', .scnम_लिखो = ioctl__scnम_लिखो_sndrv_pcm_cmd, पूर्ण,
		['T' - '$'] = { .type	= 'T', .scnम_लिखो = ioctl__scnम_लिखो_tty_cmd, पूर्ण,
		['U' - '$'] = { .type	= 'U', .scnम_लिखो = ioctl__scnम_लिखो_sndrv_ctl_cmd, पूर्ण,
		['d' - '$'] = { .type	= 'd', .scnम_लिखो = ioctl__scnम_लिखो_drm_cmd, पूर्ण,
		[0xAE - '$'] = अणु .type	= 0xAE, .scnम_लिखो = ioctl__scnम_लिखो_kvm_cmd, पूर्ण,
		[0xAF - '$'] = अणु .type	= 0xAF, .scnम_लिखो = ioctl__scnम_लिखो_vhost_virtio_cmd, पूर्ण,
	पूर्ण;
	स्थिर पूर्णांक nr_types = ARRAY_SIZE(ioctl_types);

	अगर (type >= ioctl_types[0].type && type <= ioctl_types[nr_types - 1].type) अणु
		स्थिर पूर्णांक index = type - ioctl_types[0].type;

		अगर (ioctl_types[index].scnम_लिखो != शून्य)
			वापस ioctl_types[index].scnम_लिखो(nr, dir, bf, size);
	पूर्ण

	prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%c", '(');

	अगर (dir == _IOC_NONE) अणु
		prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%s", show_prefix ? prefix : "", "NONE");
	पूर्ण अन्यथा अणु
		अगर (dir & _IOC_READ)
			prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%s", show_prefix ? prefix : "", "READ");
		अगर (dir & _IOC_WRITE) अणु
			prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%s%s", dir & _IOC_READ ? "|" : "",
					     show_prefix ? prefix : "",  "WRITE");
		पूर्ण
	पूर्ण

	वापस prपूर्णांकed + scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, ", %#x, %#x, %#x)", type, nr, sz);
पूर्ण

#अगर_अघोषित USB_DEVICE_MAJOR
#घोषणा USB_DEVICE_MAJOR 189
#पूर्ण_अगर // USB_DEVICE_MAJOR

माप_प्रकार syscall_arg__scnम_लिखो_ioctl_cmd(अक्षर *bf, माप_प्रकार size, काष्ठा syscall_arg *arg)
अणु
	अचिन्हित दीर्घ cmd = arg->val;
	पूर्णांक fd = syscall_arg__val(arg, 0);
	काष्ठा file *file = thपढ़ो__files_entry(arg->thपढ़ो, fd);

	अगर (file != शून्य) अणु
		अगर (file->dev_maj == USB_DEVICE_MAJOR)
			वापस ioctl__scnम_लिखो_usbdevfs_cmd(_IOC_NR(cmd), _IOC_सूची(cmd), bf, size);
	पूर्ण

	वापस ioctl__scnम_लिखो_cmd(cmd, bf, size, arg->show_string_prefix);
पूर्ण
