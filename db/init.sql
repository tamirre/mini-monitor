CREATE TABLE IF NOT EXISTS devices (
    id SERIAL PRIMARY KEY,
    name TEXT NOT NULL UNIQUE,
    location TEXT
);

CREATE TABLE IF NOT EXISTS measurements (
    device_id INTEGER REFERENCES devices(id),
    recorded_at TIMESTAMP NOT NULL DEFAULT NOW(),
    voltage DOUBLE PRECISION,
    current DOUBLE PRECISION,
    PRIMARY KEY (device_id, recorded_at)
);

INSERT INTO devices (name, location) VALUES ('DeviceA', 'Office') ON CONFLICT (name) DO NOTHING;
INSERT INTO devices (name, location) VALUES ('DeviceB', 'Lab') ON CONFLICT (name) DO NOTHING;
