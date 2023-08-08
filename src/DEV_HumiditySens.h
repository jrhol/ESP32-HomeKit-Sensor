struct HumSensor : Service::HumiditySensor
{
    SpanCharacteristic *hum;
    uint32_t timer = 0;

    HumSensor() : Service::HumiditySensor()
    {

        double HumC = getHum();
        hum = new Characteristic::CurrentRelativeHumidity(HumC);
    }

    void loop()
    {
        if (millis() - timer > 5000)
        { // only sample every 5 seconds
            timer = millis();

            double HumC = getHum();

            if (abs(hum->getVal<double>() - HumC) > 0.5)
            {
                hum->setVal(HumC);
            }
        }
    }
    double getHum()
    {
        if (!bme.begin())
        {
            Serial.println(F("Could not find a valid BME680 sensor, check wiring!"));
            while (1)
            {
            }
        }

        if (!bme.performReading())
        {
            Serial.println("Failed to perform reading :(");
        }

        double t = bme.humidity;
        return (t);
    }
};