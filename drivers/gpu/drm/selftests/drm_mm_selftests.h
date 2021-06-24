<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* List each unit test as selftest(name, function)
 *
 * The name is used as both an क्रमागत and expanded as igt__name to create
 * a module parameter. It must be unique and legal क्रम a C identअगरier.
 *
 * Tests are executed in order by igt/drm_mm
 */
selftest(sanitycheck, igt_sanitycheck) /* keep first (selfcheck क्रम igt) */
selftest(init, igt_init)
selftest(debug, igt_debug)
selftest(reserve, igt_reserve)
selftest(insert, igt_insert)
selftest(replace, igt_replace)
selftest(insert_range, igt_insert_range)
selftest(align, igt_align)
selftest(frag, igt_frag)
selftest(align32, igt_align32)
selftest(align64, igt_align64)
selftest(evict, igt_evict)
selftest(evict_range, igt_evict_range)
selftest(bottomup, igt_bottomup)
selftest(lowest, igt_lowest)
selftest(topकरोwn, igt_topकरोwn)
selftest(highest, igt_highest)
selftest(color, igt_color)
selftest(color_evict, igt_color_evict)
selftest(color_evict_range, igt_color_evict_range)
