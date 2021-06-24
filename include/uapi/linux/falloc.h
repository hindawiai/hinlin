<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_FALLOC_H_
#घोषणा _UAPI_FALLOC_H_

#घोषणा FALLOC_FL_KEEP_SIZE	0x01 /* शेष is extend size */
#घोषणा FALLOC_FL_PUNCH_HOLE	0x02 /* de-allocates range */
#घोषणा FALLOC_FL_NO_HIDE_STALE	0x04 /* reserved codepoपूर्णांक */

/*
 * FALLOC_FL_COLLAPSE_RANGE is used to हटाओ a range of a file
 * without leaving a hole in the file. The contents of the file beyond
 * the range being हटाओd is appended to the start offset of the range
 * being हटाओd (i.e. the hole that was punched is "collapsed"),
 * resulting in a file layout that looks like the range that was
 * हटाओd never existed. As such collapsing a range of a file changes
 * the size of the file, reducing it by the same length of the range
 * that has been हटाओd by the operation.
 *
 * Dअगरferent fileप्रणालीs may implement dअगरferent limitations on the
 * granularity of the operation. Most will limit operations to
 * fileप्रणाली block size boundaries, but this boundary may be larger or
 * smaller depending on the fileप्रणाली and/or the configuration of the
 * fileप्रणाली or file.
 *
 * Attempting to collapse a range that crosses the end of the file is
 * considered an illegal operation - just use ftruncate(2) अगर you need
 * to collapse a range that crosses खातापूर्ण.
 */
#घोषणा FALLOC_FL_COLLAPSE_RANGE	0x08

/*
 * FALLOC_FL_ZERO_RANGE is used to convert a range of file to zeros preferably
 * without issuing data IO. Blocks should be pपुनः_स्मृतिated क्रम the regions that
 * span holes in the file, and the entire range is preferable converted to
 * unwritten extents - even though file प्रणाली may choose to zero out the
 * extent or करो whatever which will result in पढ़ोing zeros from the range
 * जबतक the range reमुख्यs allocated क्रम the file.
 *
 * This can be also used to pपुनः_स्मृतिate blocks past खातापूर्ण in the same way as
 * with fallocate. Flag FALLOC_FL_KEEP_SIZE should cause the inode
 * size to reमुख्य the same.
 */
#घोषणा FALLOC_FL_ZERO_RANGE		0x10

/*
 * FALLOC_FL_INSERT_RANGE is use to insert space within the file size without
 * overwriting any existing data. The contents of the file beyond offset are
 * shअगरted towards right by len bytes to create a hole.  As such, this
 * operation will increase the size of the file by len bytes.
 *
 * Dअगरferent fileप्रणालीs may implement dअगरferent limitations on the granularity
 * of the operation. Most will limit operations to fileप्रणाली block size
 * boundaries, but this boundary may be larger or smaller depending on
 * the fileप्रणाली and/or the configuration of the fileप्रणाली or file.
 *
 * Attempting to insert space using this flag at OR beyond the end of
 * the file is considered an illegal operation - just use ftruncate(2) or
 * fallocate(2) with mode 0 क्रम such type of operations.
 */
#घोषणा FALLOC_FL_INSERT_RANGE		0x20

/*
 * FALLOC_FL_UNSHARE_RANGE is used to unshare shared blocks within the
 * file size without overwriting any existing data. The purpose of this
 * call is to preemptively पुनः_स्मृतिate any blocks that are subject to
 * copy-on-ग_लिखो.
 *
 * Dअगरferent fileप्रणालीs may implement dअगरferent limitations on the
 * granularity of the operation. Most will limit operations to fileप्रणाली
 * block size boundaries, but this boundary may be larger or smaller
 * depending on the fileप्रणाली and/or the configuration of the fileप्रणाली
 * or file.
 *
 * This flag can only be used with allocate-mode fallocate, which is
 * to say that it cannot be used with the punch, zero, collapse, or
 * insert range modes.
 */
#घोषणा FALLOC_FL_UNSHARE_RANGE		0x40

#पूर्ण_अगर /* _UAPI_FALLOC_H_ */
