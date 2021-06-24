<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <sys/socket.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/sysmacros.h>
#समावेश <sys/types.h>

#समावेश "../kselftest_harness.h"

/* Remove a file, ignoring the result अगर it didn't exist. */
व्योम rm(काष्ठा __test_metadata *_metadata, स्थिर अक्षर *pathname,
	पूर्णांक is_dir)
अणु
	पूर्णांक rc;

	अगर (is_dir)
		rc = सूची_हटाओ(pathname);
	अन्यथा
		rc = unlink(pathname);

	अगर (rc < 0) अणु
		ASSERT_EQ(त्रुटि_सं, ENOENT) अणु
			TH_LOG("Not ENOENT: %s", pathname);
		पूर्ण
	पूर्ण अन्यथा अणु
		ASSERT_EQ(rc, 0) अणु
			TH_LOG("Failed to remove: %s", pathname);
		पूर्ण
	पूर्ण
पूर्ण

FIXTURE(file) अणु
	अक्षर *pathname;
	पूर्णांक is_dir;
पूर्ण;

FIXTURE_VARIANT(file)
अणु
	स्थिर अक्षर *name;
	पूर्णांक expected;
	पूर्णांक is_dir;
	व्योम (*setup)(काष्ठा __test_metadata *_metadata,
		      FIXTURE_DATA(file) *self,
		      स्थिर FIXTURE_VARIANT(file) *variant);
	पूर्णांक major, minor, mode; /* क्रम mknod() */
पूर्ण;

व्योम setup_link(काष्ठा __test_metadata *_metadata,
		FIXTURE_DATA(file) *self,
		स्थिर FIXTURE_VARIANT(file) *variant)
अणु
	स्थिर अक्षर * स्थिर paths[] = अणु
		"/bin/true",
		"/usr/bin/true",
	पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(paths); i++) अणु
		अगर (access(paths[i], X_OK) == 0) अणु
			ASSERT_EQ(symlink(paths[i], self->pathname), 0);
			वापस;
		पूर्ण
	पूर्ण
	ASSERT_EQ(1, 0) अणु
		TH_LOG("Could not find viable 'true' binary");
	पूर्ण
पूर्ण

FIXTURE_VARIANT_ADD(file, S_IFLNK)
अणु
	.name = "S_IFLNK",
	.expected = ELOOP,
	.setup = setup_link,
पूर्ण;

व्योम setup_dir(काष्ठा __test_metadata *_metadata,
	       FIXTURE_DATA(file) *self,
	       स्थिर FIXTURE_VARIANT(file) *variant)
अणु
	ASSERT_EQ(सूची_गढ़ो(self->pathname, 0755), 0);
पूर्ण

FIXTURE_VARIANT_ADD(file, S_IFसूची)
अणु
	.name = "S_IFDIR",
	.is_dir = 1,
	.expected = EACCES,
	.setup = setup_dir,
पूर्ण;

व्योम setup_node(काष्ठा __test_metadata *_metadata,
		FIXTURE_DATA(file) *self,
		स्थिर FIXTURE_VARIANT(file) *variant)
अणु
	dev_t dev;
	पूर्णांक rc;

	dev = makedev(variant->major, variant->minor);
	rc = mknod(self->pathname, 0755 | variant->mode, dev);
	ASSERT_EQ(rc, 0) अणु
		अगर (त्रुटि_सं == EPERM)
			SKIP(वापस, "Please run as root; cannot mknod(%s)",
				variant->name);
	पूर्ण
पूर्ण

FIXTURE_VARIANT_ADD(file, S_IFBLK)
अणु
	.name = "S_IFBLK",
	.expected = EACCES,
	.setup = setup_node,
	/* /dev/loop0 */
	.major = 7,
	.minor = 0,
	.mode = S_IFBLK,
पूर्ण;

FIXTURE_VARIANT_ADD(file, S_IFCHR)
अणु
	.name = "S_IFCHR",
	.expected = EACCES,
	.setup = setup_node,
	/* /dev/zero */
	.major = 1,
	.minor = 5,
	.mode = S_IFCHR,
पूर्ण;

व्योम setup_fअगरo(काष्ठा __test_metadata *_metadata,
		FIXTURE_DATA(file) *self,
		स्थिर FIXTURE_VARIANT(file) *variant)
अणु
	ASSERT_EQ(mkfअगरo(self->pathname, 0755), 0);
पूर्ण

FIXTURE_VARIANT_ADD(file, S_IFIFO)
अणु
	.name = "S_IFIFO",
	.expected = EACCES,
	.setup = setup_fअगरo,
पूर्ण;

FIXTURE_SETUP(file)
अणु
	ASSERT_GT(aप्र_लिखो(&self->pathname, "%s.test", variant->name), 6);
	self->is_dir = variant->is_dir;

	rm(_metadata, self->pathname, variant->is_dir);
	variant->setup(_metadata, self, variant);
पूर्ण

FIXTURE_TEARDOWN(file)
अणु
	rm(_metadata, self->pathname, self->is_dir);
पूर्ण

TEST_F(file, exec_त्रुटि_सं)
अणु
	अक्षर * स्थिर argv[2] = अणु (अक्षर * स्थिर)self->pathname, शून्य पूर्ण;

	EXPECT_LT(execv(argv[0], argv), 0);
	EXPECT_EQ(त्रुटि_सं, variant->expected);
पूर्ण

/* S_IFSOCK */
FIXTURE(sock)
अणु
	पूर्णांक fd;
पूर्ण;

FIXTURE_SETUP(sock)
अणु
	self->fd = socket(AF_INET, SOCK_STREAM, 0);
	ASSERT_GE(self->fd, 0);
पूर्ण

FIXTURE_TEARDOWN(sock)
अणु
	अगर (self->fd >= 0)
		ASSERT_EQ(बंद(self->fd), 0);
पूर्ण

TEST_F(sock, exec_त्रुटि_सं)
अणु
	अक्षर * स्थिर argv[2] = अणु " magic socket ", शून्य पूर्ण;
	अक्षर * स्थिर envp[1] = अणु शून्य पूर्ण;

	EXPECT_LT(fexecve(self->fd, argv, envp), 0);
	EXPECT_EQ(त्रुटि_सं, EACCES);
पूर्ण

TEST_HARNESS_MAIN
