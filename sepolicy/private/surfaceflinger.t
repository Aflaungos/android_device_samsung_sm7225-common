allow surfaceflinger vendor_file:file { read open getattr execute map };

allow surfaceflinger vendor_firmware_file:dir { getattr read open search };

allow surfaceflinger sysfs:file { getattr read open };
