SUMMARY = "Assistive Technology Service Provider Interface (dbus core)"
DESCRIPTION = "At-Spi2 is a protocol over DBus, toolkit widgets use it to \
provide their content to screen readers such as Orca."
HOMEPAGE = "https://wiki.linuxfoundation.org/accessibility/d-bus"
LICENSE = "LGPL-2.1+"
LIC_FILES_CHKSUM = "file://COPYING;md5=4fbd65380cdd255951079008b364516c"

MAJ_VER = "${@oe.utils.trim_version("${PV}", 2)}"

SRC_URI = "${GNOME_MIRROR}/${BPN}/${MAJ_VER}/${BPN}-${PV}.tar.xz"

SRC_URI[sha256sum] = "84e36c3fe66862133f5fe229772b76aa2526e10de5014a3778f2fa46ce550da5"

X11DEPENDS = "virtual/libx11 libxi libxtst"

DEPENDS = "dbus glib-2.0"
DEPENDS += "${@bb.utils.contains('DISTRO_FEATURES', 'x11', '${X11DEPENDS}', '', d)}"

inherit meson gtk-doc gettext systemd pkgconfig upstream-version-is-even gobject-introspection

EXTRA_OEMESON = " -Dsystemd_user_dir=${systemd_user_unitdir} \
                  -Ddbus_daemon=${bindir}/dbus-daemon \
                  ${@bb.utils.contains('DISTRO_FEATURES', 'x11', '-Dx11=yes', '-Dx11=no', d)} \
"

GTKDOC_MESON_OPTION = "docs"

GIR_MESON_OPTION = 'introspection'
GIR_MESON_ENABLE_FLAG = 'yes'
GIR_MESON_DISABLE_FLAG = 'no'

FILES_${PN} += "${datadir}/dbus-1/services/*.service \
                ${datadir}/dbus-1/accessibility-services/*.service \
                ${datadir}/defaults/at-spi2 \
                ${systemd_user_unitdir}/at-spi-dbus-bus.service \
                "
BBCLASSEXTEND = "native nativesdk"
